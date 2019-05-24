
package ro.pub.cs.systems.pdsd.practicaltest02;



public class Owncontainer {

    public String queryResponse1;



    public Owncontainer(String queryResponse1)

    {

        this.queryResponse1 = queryResponse1;

    }

}

package ro.pub.cs.systems.pdsd.practicaltest02;



import android.util.Log;

import android.widget.TextView;



import java.io.BufferedReader;

import java.io.IOException;

import java.io.InputStreamReader;

import java.io.PrintWriter;

import java.net.Socket;



public class ClientThread extends Thread {

    private String address;

    private int port;

    private String query;

    private TextView showDataTextView;



    private Socket socket;



    public ClientThread(String address, int port, String query, TextView showDataTextView) {

        this.address = address;

        this.port = port;

        this.query = query;

        this.showDataTextView = showDataTextView;

    }



    public static BufferedReader getReader(Socket socket) throws IOException {

        return new BufferedReader(new InputStreamReader(socket.getInputStream()));

    }



    public static PrintWriter getWriter(Socket socket) throws IOException {

        return new PrintWriter(socket.getOutputStream(), true);

    }



    @Override

    public void run() {

        try {

            socket = new Socket(address, port);

            if (socket == null) {

                Log.e("abc", "[CLIENT THREAD] Could not create socket!");

                return;

            }

            BufferedReader bufferedReader = getReader(socket);

            PrintWriter printWriter = getWriter(socket);

            if (bufferedReader == null || printWriter == null) {

                Log.e("abc", "[CLIENT THREAD] Buffered Reader / Print Writer are null!");

                return;

            }



            // We send the first querry to the communicaiton thread (city)

            printWriter.println(query);

            printWriter.flush();



            StringBuilder finfin = new StringBuilder();

            String weatherInformation;

            while ((weatherInformation = bufferedReader.readLine()) != null) {

                Log.d("abc", weatherInformation);

                finfin.append(weatherInformation);

            }

            final String finalizedWeateherInformation = finfin.toString();

            showDataTextView.post(new Runnable() {

                @Override

                public void run() {



                    showDataTextView.setText(finalizedWeateherInformation);

                }

            });

        } catch (IOException ioException) {

            Log.e("abc", "[CLIENT THREAD] An exception has occurred: " + ioException.getMessage());



        } finally {

            if (socket != null) {

                try {

                    socket.close();

                } catch (IOException ioException) {

                    Log.d("abc", "nu merge");

                }

            }

        }

    }

}




package ro.pub.cs.systems.pdsd.practicaltest02;



import android.util.Log;



import java.io.IOException;

import java.net.ServerSocket;

import java.net.Socket;

import java.util.HashMap;



import cz.msebera.android.httpclient.client.ClientProtocolException;



public class ServerThread extends Thread {

    private int port = 0;

    private ServerSocket serverSocket = null;



    private HashMap<String, Owncontainer> data = null;



    public ServerThread(int port) {

        this.port = port;

        try {

            this.serverSocket = new ServerSocket(port);

        } catch (IOException ioException) {



        }

        this.data = new HashMap<>();

    }



    public void setPort(int port) {

        this.port = port;

    }



    public int getPort() {

        return port;

    }



    public void setServerSocket(ServerSocket serverSocket) {

        this.serverSocket = serverSocket;

    }



    public ServerSocket getServerSocket() {

        return serverSocket;

    }



    public synchronized void setData(String city, Owncontainer weatherForecastInformation) {

        this.data.put(city, weatherForecastInformation);

    }



    public synchronized HashMap<String, Owncontainer> getData() {

        return data;

    }



    @Override

    public void run() {

        try {

            while (!Thread.currentThread().isInterrupted()) {

                Log.i("abc", "[SERVER THREAD] Waiting for a client invocation...");

                Socket socket = serverSocket.accept();

                Log.i("abc", "[SERVER THREAD] A connection request was received from " + socket.getInetAddress() + ":" + socket.getLocalPort());

                CommunicationThread communicationThread = new CommunicationThread(this, socket);

                communicationThread.start();

            }

        } catch (ClientProtocolException clientProtocolException) {

            Log.i("abc", "nu a mers");

        } catch (IOException e) {

            e.printStackTrace();

        }

    }



    public void stopThread() {

        interrupt();

        if (serverSocket != null) {

            try {

                serverSocket.close();

            } catch (IOException ioException) {

                Log.i("abc", "nu a mers");

            }

        }

    }

}


package ro.pub.cs.systems.pdsd.practicaltest02;



import android.util.Log;



import org.json.JSONObject;

import org.jsoup.Jsoup;

import org.jsoup.nodes.Document;

import org.jsoup.nodes.Element;

import org.jsoup.select.Elements;



import java.io.BufferedReader;

import java.io.IOException;

import java.io.InputStreamReader;

import java.io.PrintWriter;

import java.net.Socket;

import java.util.ArrayList;

import java.util.HashMap;

import java.util.List;



import cz.msebera.android.httpclient.NameValuePair;

import cz.msebera.android.httpclient.client.HttpClient;

import cz.msebera.android.httpclient.client.ResponseHandler;

import cz.msebera.android.httpclient.client.methods.HttpGet;

import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;

import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;



public class CommunicationThread extends Thread {

    private ServerThread serverThread;

    private Socket socket;



    public CommunicationThread(ServerThread serverThread, Socket socket) {

        this.serverThread = serverThread;

        this.socket = socket;

    }



    public static BufferedReader getReader(Socket socket) throws IOException {

        return new BufferedReader(new InputStreamReader(socket.getInputStream()));

    }



    public static PrintWriter getWriter(Socket socket) throws IOException {

        return new PrintWriter(socket.getOutputStream(), true);

    }





    @Override

    public void run() {

        if (socket == null) {

            Log.e("abc", "[COMMUNICATION THREAD] Socket is null!");

            return;

        }

        Log.d("abc", "Started Communication Thread");

        try {

            BufferedReader bufferedReader = getReader(socket);

            PrintWriter printWriter = getWriter(socket);



            if (bufferedReader == null || printWriter == null) {

                Log.e("abc", "[COMMUNICATION THREAD] Buffered Reader / Print Writer are null!");

                return;

            }

            Log.i("abc", "[COMMUNICATION THREAD] Waiting for parameters from client (city / information type!");





            // We read the first query sent in the ClientThread

            String query1 = bufferedReader.readLine();





            if (query1 == null || query1.isEmpty()) {

                Log.e("abc", "[COMMUNICATION THREAD] Error receiving parameters from client (query1 / information type!");

                return;

            }



            HashMap<String, Owncontainer> dataServer = serverThread.getData();

            Owncontainer responseData;

            String result;



            if (dataServer.containsKey(query1)) {

                Log.i("abc", "[COMMUNICATION THREAD] Getting the information from the cache...");

                responseData = dataServer.get(query1);



            } else {

                Log.i("abc", "[COMMUNICATION THREAD] Getting the information from the webservice...");

                HttpClient httpClient = new DefaultHttpClient();

                // In case of POST change to HttpPost and remover the arghuments from the urkl

                HttpGet httpPost = new HttpGet("http://services.aonaware.com/DictService/DictService.asmx/Define?word=" + query1);

                List<NameValuePair> params = new ArrayList<>();



                ResponseHandler<String> responseHandler = new BasicResponseHandler();

                String pageSourceCode = httpClient.execute(httpPost, responseHandler);

                if (pageSourceCode == null) {

                    Log.e("abc", "[COMMUNICATION THREAD] Error getting the information from the webservice!");

                    return;

                }

                /*

                Document document = Jsoup.parse(pageSourceCode);

                Element element = document.child(0);





                Elements elements = element.getElementsByTag("WordDefinition");

                Log.d("abc", elements.text());

                String querryData = elements.get(0).text();



                Log.d("abc", query1);

                */

                int st = pageSourceCode.indexOf("<WordDefinition>");

                int end = pageSourceCode.indexOf("</WordDefinition>");

                String querryData = pageSourceCode.substring(st + "<WordDefinition>".length(), end);

                responseData = new Owncontainer(querryData);





                serverThread.setData(query1, responseData);





            }

            result = responseData.queryResponse1;



            // Send the data to the client

            printWriter.println(result);

            printWriter.flush();



            socket.close();

        }catch (Exception e){

            Log.d("abc", "Exceptie: + " + e);

        }

    }

}




package ro.pub.cs.systems.pdsd.practicaltest02;



import android.support.v7.app.AppCompatActivity;

import android.os.Bundle;

import android.view.View;

import android.widget.Button;

import android.widget.EditText;

import android.widget.TextView;



public class PracticalTest02MainActivity extends AppCompatActivity {



    TextView defin;

    EditText serverPort, clientPort, address, city;

    Button connect, get;



    ServerThread serverThread = null;

    ClientThread clientThread = null;



    @Override

    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_practical_test02_main);



        serverPort = (EditText) findViewById(R.id.serverPort);

        clientPort = findViewById(R.id.clientPort);

        address = findViewById(R.id.address);

        city = findViewById(R.id.city);

        connect = findViewById(R.id.connect);

        get = findViewById(R.id.weather);

        defin = findViewById(R.id.weatherView);



        connect.setOnClickListener(new View.OnClickListener() {

            @Override

            public void onClick(View v) {

                String svPort = serverPort.getText().toString();

                if (svPort != null && !svPort.isEmpty()) {

                    serverThread = new ServerThread(Integer.parseInt(svPort));

                    serverThread.start();

                }

            }

        });



        get.setOnClickListener(new View.OnClickListener() {

            @Override

            public void onClick(View v) {

                String query = city.getText().toString();



                String clPort = clientPort.getText().toString();

                String clAddress = address.getText().toString();



                clientThread = new ClientThread(clAddress, Integer.parseInt(clPort), query, defin);

                clientThread.start();

            }

        });



    }



    @Override

    protected void onDestroy() {



        if (serverThread != null)

            serverThread.stopThread();

        super.onDestroy();





    }

}
