package com.example.colocviu2;

import android.util.Log;
import android.widget.TextView;

import com.example.colocviu2.model.Exchange;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;


public class ClientThread extends Thread {

    private String address;
    private int port;
    private String coinType;
    private String informationType;
    private TextView response;

    private Socket socket;

    public ClientThread(String address, int port, String coinType, TextView response) {
        this.address = address;
        this.port = port;
        this.coinType = coinType;
        this.response = response;
    }

    @Override
    public void run() {
        try {
            socket = new Socket(address, port);
            if (socket == null) {
                //Log.e(Constants.TAG, "[CLIENT THREAD] Could not create socket!");
                return;
            }
            BufferedReader bufferedReader = Utilities.getReader(socket);
            PrintWriter printWriter = Utilities.getWriter(socket);
            if (bufferedReader == null || printWriter == null) {
                //Log.e(Constants.TAG, "[CLIENT THREAD] Buffered Reader / Print Writer are null!");
                return;
            }
            printWriter.println(coinType);
            printWriter.flush();
            String exchangeInfo;
            while ((exchangeInfo = bufferedReader.readLine()) != null) {
                final String finalizedExchangeInformation = exchangeInfo;
                response.post(new Runnable() {
                    @Override
                    public void run() {
                        Gson gson = new GsonBuilder().create();
                        Exchange e = gson.fromJson(finalizedExchangeInformation, Exchange.class);
                        response.setText(e.bpi.USD.rate + " " + e.bpi.USD.description);
                    }
                });
            }
        } catch (IOException ioException) {
            Log.e("Exceptie", "[CLIENT THREAD] An exception has occurred: " + ioException.getMessage());
        } finally {
            if (socket != null) {
                try {
                    socket.close();
                } catch (IOException ioException) {
                    Log.e("Exceptie", "[CLIENT THREAD] An exception has occurred: " + ioException.getMessage());
                }
            }
        }
    }

}




package com.example.colocviu2;

import android.util.Log;

import com.example.colocviu2.model.Exchange;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class ServerThread extends Thread {

    public int port = 0;
    public ServerSocket serverSocket = null;

    public Exchange data = new Exchange();

    public ServerThread(int port) {
        this.port = port;
        try {
            this.serverSocket = new ServerSocket(port);
        } catch (IOException ioException) {
            System.out.println(ioException.toString());
            System.out.println("Exceptie server");
        }
    }


    public void setServerSocket(ServerSocket serverSocket) {
        this.serverSocket = serverSocket;
    }


    public synchronized void setData(Exchange data) {
        this.data = data;
    }

    public synchronized Exchange getData() {
        return data;
    }

    @Override
    public void run() {
        try {
            while (!Thread.currentThread().isInterrupted()) {
                Socket socket = serverSocket.accept();
                //Log.i(Constants.TAG, "[SERVER THREAD] A connection request was received from " + socket.getInetAddress() + ":" + socket.getLocalPort());
                CommunicationThread communicationThread = new CommunicationThread(this, socket);
                communicationThread.start();
            }
        } catch (Exception clientProtocolException) {
            Log.e("Exception", "[SERVER THREAD] An exception has occurred: " + clientProtocolException.getMessage());
        }
    }
}

    /*public void stopThread() {
        interrupt();
        if (serverSocket != null) {
            try {
                serverSocket.close();
            } catch (IOException ioException) {
                Log.e(Constants.TAG, "[SERVER THREAD] An exception has occurred: " + ioException.getMessage());
                if (Constants.DEBUG) {
                    ioException.printStackTrace();
                }
            }
        }
    }*/



	
	
	
	package com.example.colocviu2;

import android.util.Log;

import com.example.colocviu2.model.Exchange;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import org.json.JSONException;
import org.json.JSONObject;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.HttpURLConnection;
import java.net.Socket;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class CommunicationThread extends Thread {

    private ServerThread serverThread;
    private Socket socket;

    public CommunicationThread(ServerThread serverThread, Socket socket) {
        this.serverThread = serverThread;
        this.socket = socket;
    }

    @Override
    public void run() {
        if (socket == null) {
            return;
        }
        try {
            BufferedReader bufferedReader = Utilities.getReader(socket);
            PrintWriter printWriter = Utilities.getWriter(socket);
            if (bufferedReader == null || printWriter == null) {
                //Log.e(Constants.TAG, "[COMMUNICATION THREAD] Buffered Reader / Print Writer are null!");
                return;
            }

            String coinType = bufferedReader.readLine();
            System.out.println(coinType + " communication thread");

            URL obj = new URL("http://api.coindesk.com/v1/bpi/currentprice/EUR.json");
            HttpURLConnection con = (HttpURLConnection) obj.openConnection();
            con.setRequestMethod("GET");
            int responseCode = con.getResponseCode();
            System.out.println("Sending 'GET' request to URL");
            System.out.println("Response Code : " + responseCode);
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(con.getInputStream()));
            String inputLine;
            StringBuffer response = new StringBuffer();

            while ((inputLine = in.readLine()) != null) {
                response.append(inputLine);
            }
            in.close();

            //print result
            System.out.println(response.toString());
            Gson gson = new GsonBuilder().create();
            Exchange e = gson.fromJson(response.toString(), Exchange.class);
            System.out.println("RASPUNS:");
            System.out.println(e.bpi.USD.description);

            printWriter.println(response.toString());
            printWriter.flush();

        } catch (Exception e) {
            System.out.println(e);
        }

    }

}



package com.example.colocviu2;


public class Coin{
    public String code;
    public String rate;
    public String description;
    public float rate_float;

    public Coin(String code, String rate, String description, float rate_float) {
        this.code = code;
        this.rate = rate;
        this.description = description;
        this.rate_float = rate_float;
    }
}
