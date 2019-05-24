package ro.pub.cs.systems.eim.lab06.earthshake.network;

import android.os.AsyncTask;
import android.util.Log;
import android.widget.ListView;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import cz.msebera.android.httpclient.client.ClientProtocolException;
import cz.msebera.android.httpclient.client.HttpClient;
import cz.msebera.android.httpclient.client.ResponseHandler;
import cz.msebera.android.httpclient.client.methods.HttpGet;
import cz.msebera.android.httpclient.impl.client.BasicResponseHandler;
import cz.msebera.android.httpclient.impl.client.DefaultHttpClient;

import ro.pub.cs.systems.eim.lab06.earthshake.general.Utilities;
import ro.pub.cs.systems.eim.lab06.earthshake.general.Constants;

public class Task extends AsyncTask<String, Void, List<Utilities>> {

    private ListView earthquakeListView;

    public Task(ListView earthquakeListView) {
        this.earthquakeListView = earthquakeListView;
    }

    @Override
    protected List<Utilities> doInBackground(String... params) {
        HttpClient httpClient = new DefaultHttpClient();
        String url = Constants.EARTHQUAKE_LISTER_WEB_SERVICE_INTERNET_ADDRESS +
                Constants.NORTH + params[Constants.NORTH_INDEX] +
                "&" + Constants.SOUTH + params[Constants.SOUTH_INDEX] +
                "&" + Constants.EAST + params[Constants.EAST_INDEX] +
                "&" + Constants.WEST + params[Constants.WEST_INDEX] +
                "&" + Constants.CREDENTIALS;
        Log.d(Constants.TAG, "url=" + url);
        HttpGet httpGet = new HttpGet(url);
        ResponseHandler<String> responseHandler = new BasicResponseHandler();

        try {
            String content = httpClient.execute(httpGet, responseHandler);
            Log.d(Constants.TAG, "content=" + content);
            List<Utilities> earthquakeInformationList = new ArrayList<>();
            JSONObject result = new JSONObject(content);
            JSONArray jsonArray = result.getJSONArray(Constants.BPI);
            for(int i = 0; i < jsonArray.length(); ++i){
                JSONObject jsonObject = jsonArray.getJSONObject(i);

                /*earthquakeInformationList.add(new Utilities(
                        jsonObject.getDouble(Constants.LATITUDE),
                        jsonObject.getDouble(Constants.LONGITUDE),
                        jsonObject.getDouble(Constants.MAGNITUDE),
                        jsonObject.getDouble(Constants.DEPTH),
                        jsonObject.getString(Constants.SOURCE),
                        jsonObject.getString(Constants.DATE_AND_TIME)
                ));*/
            }
            return earthquakeInformationList;
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
        return null;
    }
    //@Override
    /*public void onPostExecute(List<Utilities> earthquakeInformationList) {
        earthquakeListView.setAdapter(new InfoAdapter(
                earthquakeListView.getContext(),
                earthquakeInformationList
        ));
    }*/
}
























