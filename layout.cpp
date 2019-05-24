Skip to content

 
Why GitHub?  
Enterprise 
Explore  
Marketplace 
Pricing  
  
Sign in 
Sign up 


 Watch 
0 
 Star 
0 
 Fork 
0 

blu3pirate/model 
 Code 
 Issues 0 
 Pull requests 0 
 Projects 0 
  Security 
 Insights 
Dismiss 
Join GitHub today
GitHub is home to over 36 million developers working together to host and review code, manage projects, and build software together.
Sign up 
Branch: master 
model/test/app/src/main/res/layout/activity_practical_test02_main.xml 
Find file 
Copy path 
 blu3pirate Add files via upload 
cca3041 17 hours ago 
1 contributor 
98 lines (85 sloc) 3.03 KB 
Raw
Blame
History
   

<?xml version="1.0" encoding="utf-8"?>

<LinearLayout

    xmlns:android="http://schemas.android.com/apk/res/android"

    xmlns:app="http://schemas.android.com/apk/res-auto"

    xmlns:tools="http://schemas.android.com/tools"

    android:layout_width="match_parent"

    android:layout_height="match_parent"

    tools:context=".PracticalTest02MainActivity"

    android:orientation="vertical">



    <TextView

        android:id="@+id/serverText"

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:text="SERVER"

        android:gravity="center"

        android:enabled="false"/>



    <LinearLayout

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:orientation="horizontal">



        <EditText

            android:id="@+id/serverPort"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:hint="Port"

            android:enabled="true"

            android:layout_weight="1"/>



        <Button

            android:id="@+id/connect"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:text="Connect"

            android:layout_weight="1"/>

    </LinearLayout>



    <TextView

        android:id="@+id/clientText"

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:text="CLIENT"

        android:gravity="center"

        android:enabled="false"/>



    <LinearLayout

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:orientation="horizontal">



        <EditText

            android:id="@+id/address"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:hint="Address"

            android:enabled="true"

            android:layout_weight="1"/>



        <EditText

            android:id="@+id/clientPort"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:hint="Port"

            android:text=""

            android:enabled="true"

            android:layout_weight="1"/>

    </LinearLayout>



    <LinearLayout

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:orientation="horizontal">



        <EditText

            android:id="@+id/city"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:hint="Word"

            android:enabled="true"

            android:layout_weight="1"/>



        <Button

            android:id="@+id/weather"

            android:layout_width="wrap_content"

            android:layout_height="wrap_content"

            android:text="Get"

            android:layout_weight="1"/>

    </LinearLayout>



    <TextView

        android:id="@+id/weatherView"

        android:layout_width="match_parent"

        android:layout_height="wrap_content"

        android:text="Aici apare definitia"/>



</LinearLayout>

© 2019 GitHub, Inc.
Terms
Privacy
Security
Status
Help
 
Contact GitHub
Pricing
API
Training
Blog
About





<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
xmlns:app="http://schemas.android.com/apk/res-auto"
xmlns:tools="http://schemas.android.com/tools"
android:layout_width="match_parent"
android:layout_height="match_parent"
android:orientation="vertical"
tools:context="ro.pub.cs.systems.eim.lab06.earthshake.view.PracticalTest">

<TextView
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_gravity="center"
    android:textSize="25sp"
    android:textStyle="bold"
    android:text="SERVER"
    />

<LinearLayout
    android:layout_width="match_parent"
    android:layout_height="wrap_content"
    android:baselineAligned="false">

    <ScrollView
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_weight="1">

        <EditText
            android:id="@+id/server_port"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:hint="Server_port"/>

    </ScrollView>

    <ScrollView
        android:layout_width="0dp"
        android:layout_height="wrap_content"
        android:layout_weight="1">

        <Button
            android:id="@+id/connect"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:textSize="14sp"
            android:textStyle="bold"
            android:layout_gravity="center"
            android:text="CONNECT"
            />

    </ScrollView>

</LinearLayout>

<TextView
    android:layout_width="wrap_content"
    android:layout_height="wrap_content"
    android:layout_gravity="center"
    android:textSize="25sp"
    android:textStyle="bold"
    android:text="CLIENT"
    />

<GridLayout
    android:layout_width="match_parent"
    android:layout_height="wrap_content"
    android:rowCount="2"
    android:columnCount="2">

    <EditText
        android:id="@+id/client_addr"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:ems="5"
        android:hint="Client_addr"
        android:layout_gravity="center"
        android:layout_row="0"
        android:layout_column="0"/>

    <EditText
        android:id="@+id/client_port"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:ems="5"

        android:hint="Client_port"
        android:layout_row="1"
        android:layout_column="0"/>

    <EditText
        android:id="@+id/valuta"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:ems="5"
        android:hint="EUR/USD"
        android:layout_gravity="right"
        android:layout_row="0"
        android:layout_column="1"/>

    <Button
        android:id="@+id/send"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:textSize="14sp"
        android:textStyle="bold"
        android:layout_row="1"
        android:layout_gravity="right"
        android:layout_column="1"
        android:text="SHOW" />

</GridLayout>

    <ScrollView
        android:layout_width="match_parent"
        android:layout_height="match_parent">

        <TextView
            android:id="@+id/current_val"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:maxLines="10"/>

    </ScrollView>

</LinearLayout>







<?xml version="1.0" encoding="utf-8"?>
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    xmlns:app="http://schemas.android.com/apk/res-auto"
    xmlns:tools="http://schemas.android.com/tools"
    android:layout_width="match_parent"
    android:layout_height="match_parent"
    android:orientation="vertical"
    tools:context=".MainActivity">

    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_gravity="center"
        android:textSize="25sp"
        android:textStyle="bold"
        android:text="Server"/>

    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:baselineAligned="false">

        <ScrollView
            android:layout_width="0dp"
            android:layout_height="wrap_content"
            android:layout_weight="1">

            <EditText
                android:id="@+id/server_port_edit_text"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:hint="Port number"/>

        </ScrollView>

        <ScrollView
            android:layout_width="0dp"
            android:layout_height="wrap_content"
            android:layout_weight="1">

            <Button
                android:id="@+id/connect_button"
                android:layout_width="wrap_content"
                android:layout_height="wrap_content"
                android:layout_gravity="center"
                android:text="Connect"/>

        </ScrollView>

    </LinearLayout>

    <Space
        android:layout_width="wrap_content"
        android:layout_height="10dp" />

    <TextView
        android:layout_width="wrap_content"
        android:layout_height="wrap_content"
        android:layout_gravity="center"
        android:textSize="25sp"
        android:textStyle="bold"
        android:text="Client"/>

    <LinearLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:baselineAligned="false">

        <ScrollView
            android:layout_width="0dp"
            android:layout_height="wrap_content"
            android:layout_weight="1">

            <EditText
                android:id="@+id/client_address_edit_text"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:hint="Adresa  (url sau host)"/>

        </ScrollView>

        <ScrollView
            android:layout_width="0dp"
            android:layout_height="wrap_content"
            android:layout_weight="1">

            <EditText
                android:id="@+id/client_port_edit_text"
                android:layout_width="match_parent"
                android:layout_height="wrap_content"
                android:hint="Port"/>

        </ScrollView>

    </LinearLayout>

    <GridLayout
        android:layout_width="match_parent"
        android:layout_height="wrap_content"
        android:rowCount="2"
        android:columnCount="2">

        <EditText
            android:id="@+id/city_edit_text"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:ems="5"
            android:hint="Valuta"
            android:layout_row="0"
            android:layout_column="0"/>


        <Button
            android:id="@+id/get_weather_forecast_button"
            android:layout_width="wrap_content"
            android:layout_height="wrap_content"
            android:layout_gravity="center"
            android:text="Obtine date"
            android:layout_row="0"
            android:layout_rowSpan="2"
            android:layout_column="1"/>

    </GridLayout>

    <ScrollView
        android:layout_width="match_parent"
        android:layout_height="match_parent">

        <TextView
            android:id="@+id/weather_forecast_text_view"
            android:layout_width="match_parent"
            android:layout_height="wrap_content"
            android:maxLines="10"/>

    </ScrollView>

</LinearLayout>
































