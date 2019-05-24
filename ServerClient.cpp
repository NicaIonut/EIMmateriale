package ro.pub.cs.systems.eim.lab06.earthshake.network;

import android.util.Log;
import android.widget.EditText;

import java.io.IOException;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

import ro.pub.cs.systems.eim.lab06.earthshake.general.Constants;

public class Server extends Thread {

    private boolean isRunning;

    public ServerSocket serverSocket;

    private EditText server_port;

    public Server(EditText server_port) {
        this.server_port = server_port;
    }

    public void startServer() {
        isRunning = true;
        start();
        Log.v(Constants.TAG, "startServer() method was invoked");
    }

    /*public void stopServer() {
        isRunning = false;
        try {
            serverSocket.close();
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (Constants.DEBUG) {
                ioException.printStackTrace();
            }
        }
        Log.v(Constants.TAG, "stopServer() method was invoked");
    }*/

    @Override
    public void run() {
        try {
            Log.v(Constants.TAG, "accept()-ed port: " + server_port.getText().toString());
            serverSocket = new ServerSocket(Integer.parseInt(server_port.getText().toString()),
                    50, InetAddress.getByName("0.0.0.0"));
                while (isRunning) {
                    Socket socket = serverSocket.accept();
                    Log.v(Constants.TAG, "accept()-ed: " + socket.getInetAddress());
                    if (socket != null) {
                        Comunication communicationThread = new Comunication(socket, server_port);
                        communicationThread.start();
                    }
            }
        } catch (IOException ioException) {
            Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            if (true) {
                ioException.printStackTrace();
            }
        }
    }
}










package ro.pub.cs.systems.eim.lab06.earthshake.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import ro.pub.cs.systems.eim.lab06.earthshake.general.Utilities;

public class Client extends AsyncTask<String, String, Void> {

    private TextView serverMessageTextView;

    public Client(TextView serverMessageTextView) {
        this.serverMessageTextView = serverMessageTextView;
    }

    @Override
    protected Void doInBackground(String... params) {
        Socket socket = null;
        try {
            String serverAddress = params[0];
            int serverPort = Integer.parseInt(params[1]);
            String valuta = params[2];
            socket = new Socket(serverAddress, serverPort);
            if (socket == null) {
                return null;
            }

            BufferedReader bufferedReader = Utilities.getReader(socket);

            PrintWriter printWriter = Utilities.getWriter(socket);

            if (bufferedReader == null || printWriter == null) {
               /// Log.e("abc", "[CLIENT THREAD] Buffered Reader / Print Writer are null!");
                return null;
            }

            //printWriter.println(valuta);
           // printWriter.flush();
            //Log.v(Constants.TAG, "Connection opened with " + socket.getInetAddress() + ":" + socket.getLocalPort());
            //BufferedReader bufferedReader = Utilities.getReader(socket);
            String currentLine;
            while ((currentLine = bufferedReader.readLine()) != null) {
                publishProgress(currentLine);
            }
        } catch (IOException ioException) {
            //Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            //if (Constants.DEBUG) {
                ioException.printStackTrace();
           // }
        } finally {
            try {
                if (socket != null) {
                    socket.close();
                }
                //Log.v(Constants.TAG, "Connection closed");
            } catch (IOException ioException) {
               // Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
                //if (Constants.DEBUG) {
                    ioException.printStackTrace();
                //}
            }
        }
        return null;
    }

    @Override
    protected void onPreExecute() {
        serverMessageTextView.setText("");
    }

    @Override
    protected void onProgressUpdate(String... progress) {
        serverMessageTextView.append(progress[0] + "\n");
    }

    @Override
    protected void onPostExecute(Void result) {}

}











package ro.pub.cs.systems.eim.lab06.earthshake.network;

import android.util.Log;
import android.widget.EditText;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;
import ro.pub.cs.systems.eim.lab06.earthshake.general.Constants;
import ro.pub.cs.systems.eim.lab06.earthshake.general.Utilities;

public class Comunication extends Thread {
    private Socket socket;
    private EditText serverTextEditText;

    public Comunication(Socket socket, EditText serverTextEditText) {
        this.socket = socket;
        this.serverTextEditText = serverTextEditText;
    }

    @Override
    public void run() {
        try {
            HttpClient httpClient = new DefaultHttpClient();
            String url = Constants.WEB;
            Log.d(Constants.TAG, "url=" + url);
            HttpGet httpGet = new HttpGet(url);
            ResponseHandler<String> responseHandler = new BasicResponseHandler();

            try {
                String content = httpClient.execute(httpGet, responseHandler);
                Log.d(Constants.TAG, "content=" + content);
                //List<Utilities> earthquakeInformationList = new ArrayList<>();
                JSONObject result = new JSONObject(content);
                JSONObject bpi = result.getJSONObject(Constants.BPI);
                Log.d(Constants.TAG, "eur=" + bpi);
                JSONObject eur = bpi.getJSONObject(Constants.EUR);

                Log.d(Constants.TAG, "content=" + eur.getDouble(Constants.VALUTA));

                //return earthquakeInformationList;
            } catch (JSONException jsonException) {
                Log.e(Constants.TAG, jsonException.getMessage());
                if (Constants.DEBUG) {
                    jsonException.printStackTrace();
                }
            } catch (ClientProtocolException clientProtocolException) {
                Log.e(Constants.TAG, clientProtocolException.getMessage());
                if (Constants.DEBUG) {
                    clientProtocolException.printStackTrace();
                }
            } catch (IOException ioException) {
                Log.e(Constants.TAG, ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }

            //Log.v(Constants.TAG, "Connection opened to " + socket.getLocalAddress() + ":" + socket.getLocalPort()+ " from " + socket.getInetAddress());
            PrintWriter printWriter = Utilities.getWriter(socket);
            printWriter.println(serverTextEditText.getText().toString());
            socket.close();
            //Log.v(Constants.TAG, "Connection closed");
        } catch (IOException ioException) {
           // Log.e(Constants.TAG, "An exception has occurred: " + ioException.getMessage());
            //if (Constants.DEBUG) {
                ioException.printStackTrace();
            //}
        }
    }
}



















package ro.pub.cs.systems.eim.lab06.earthshake.view;

import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import ro.pub.cs.systems.eim.lab06.earthshake.R;
import ro.pub.cs.systems.eim.lab06.earthshake.general.Constants;
import ro.pub.cs.systems.eim.lab06.earthshake.network.Client;
import ro.pub.cs.systems.eim.lab06.earthshake.network.Server;
import ro.pub.cs.systems.eim.lab06.earthshake.network.Task;

public class PracticalTest extends AppCompatActivity {
    private EditText server_port, client_port, client_addr, valuta;
    private Button connect, send;
    public TextView response = null;
    private Server serverThread = null;
    private Client clientThread = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        server_port = (EditText)findViewById(R.id.server_port);
        client_addr = (EditText)findViewById(R.id.client_addr);
        client_port = (EditText)findViewById(R.id.client_port);
        valuta = (EditText)findViewById(R.id.valuta);

        connect = (Button)findViewById(R.id.connect);
        send = (Button)findViewById(R.id.send);

        response = (TextView) findViewById(R.id.current_val);

        connect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String serverPortString = server_port.getText().toString();
                if (serverPortString == null || serverPortString.isEmpty()) {
                    Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] Server port should be filled!", Toast.LENGTH_SHORT).show();
                    return;
                }
                serverThread = new Server(server_port);

                serverThread.startServer();
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String clientAddress = client_addr.getText().toString();
                String clientPortString = client_port.getText().toString();
                if (clientAddress == null || clientAddress.isEmpty()
                        || clientPortString == null || clientPortString.isEmpty()) {
                    Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] Client connection parameters should be filled!", Toast.LENGTH_SHORT).show();
                    return;
                }

                String coinType = valuta.getText().toString();

                if (coinType == null || coinType.isEmpty()) {
                    Toast.makeText(getApplicationContext(), "[MAIN ACTIVITY] Parameters from client (city / information type) should be filled", Toast.LENGTH_SHORT).show();
                    return;
                }
                clientThread = new Client(response);
                clientThread.execute(clientAddress,clientPortString, coinType);

            }
        });

    }
}






package ro.pub.cs.systems.eim.lab06.earthshake.general;

public interface Constants {

    final public static boolean DEBUG = true;

    final public static String TAG = "[Earthquake Lister]";
    final public static String WEB = "https://api.coindesk.com/v1/bpi/currentprice/EUR.json";
    final public static String EARTHQUAKE_LISTER_WEB_SERVICE_INTERNET_ADDRESS = "http://api.geonames.org/earthquakesJSON?";

    final public static String MISSING_INFORMATION_ERROR_MESSAGE = "All fields need to be completed!";

    final public static String NORTH = "north=";
    final public static String SOUTH = "south=";
    final public static String EAST = "east=";
    final public static String WEST = "west=";
    final public static int NORTH_INDEX = 0;
    final public static int SOUTH_INDEX = 1;
    final public static int EAST_INDEX = 2;
    final public static int WEST_INDEX = 3;
    final public static String CREDENTIALS = "username=eim2017";
    final public static String VALUTA = "rate";
    final public static String BPI = "bpi";
    final public static String EUR = "EUR";
    final public static String EARTHQUAKES = "earthquakes";
    final public static String LATITUDE = "lat";
    final public static String LONGITUDE = "lng";
    final public static String MAGNITUDE = "magnitude";
    final public static String DEPTH = "depth";
    final public static String SOURCE = "src";
    final public static String DATE_AND_TIME = "datetime";


}




package ro.pub.cs.systems.eim.lab06.earthshake.general;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class Utilities {
    public static BufferedReader getReader(Socket socket) throws IOException {
        return new BufferedReader(new InputStreamReader(socket.getInputStream()));
    }

    public static PrintWriter getWriter(Socket socket) throws IOException {
        return new PrintWriter(socket.getOutputStream(), true);
    }
}





