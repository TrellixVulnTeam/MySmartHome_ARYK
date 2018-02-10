package com.smarthome.thorben.smarthome;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import org.eclipse.paho.android.service.MqttAndroidClient;
import org.eclipse.paho.client.mqttv3.IMqttActionListener;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.IMqttToken;
import org.eclipse.paho.client.mqttv3.MqttCallback;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;

public class HomeActivity extends AppCompatActivity{

    private MqttAndroidClient client;
    private TextView humid;
    private TextView temp;
    private TextView tau;
    private TextView floor;


    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        humid = (TextView) findViewById(R.id.textViewTemp);
        temp = (TextView) findViewById(R.id.textViewHumid);
        tau = (TextView) findViewById(R.id.textViewTau);
        floor = (TextView) findViewById(R.id.textViewFloor);

        humid.setText("0");
        temp.setText("0");
        tau.setText("0");

        floor.setText("Etage:");

        ToggleButton toggle_mode = (ToggleButton) findViewById(R.id.toggleButtonAdvanced);
        toggle_mode.setOnCheckedChangeListener(toggleListenerAdvanced);

        ToggleButton toggle_floor = (ToggleButton) findViewById(R.id.toggleButtonFloor);
        toggle_floor.setOnCheckedChangeListener(toggleListenerFloor);


        String clientId = MqttClient.generateClientId();
        client = new MqttAndroidClient(this.getApplicationContext(), "tcp://192.168.178.102:1883", clientId);

        try {
            IMqttToken token;
            token = client.connect();
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    Toast.makeText(HomeActivity.this, "Verbunden!", Toast.LENGTH_LONG).show();

                    setSubscription("temp_thorben");
                    setSubscription("humid_thorben");
                    setSubscription("tau_thorben");
                    setSubscription("air_thorben");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    Toast.makeText(HomeActivity.this, "Verbinden fehlgeschlagen!", Toast.LENGTH_LONG).show();
                }
            });
        } catch (MqttException e) {
            Toast.makeText(HomeActivity.this, "Mittendrin!", Toast.LENGTH_LONG).show();
            e.printStackTrace();
        }

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {

                if (topic.equals("temp_thorben")) {
                    temp.setText(new String(message.getPayload()));
                } else if (topic.equals("humid_thorben")) {
                    humid.setText(new String(message.getPayload()));
                } else if (topic.equals("tau_thorben")) {
                    tau.setText(new String(message.getPayload()));
                } else if (topic.equals("air_thorben")) {
                    //advice.setText(new String(message.getPayload()));
                }
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });

    }

    private void setSubscription(String topic) {
        try {
            client.subscribe(topic, 0);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    CompoundButton.OnCheckedChangeListener toggleListenerAdvanced = new CompoundButton.OnCheckedChangeListener() {

        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            if (isChecked) {
                Toast.makeText(HomeActivity.this, "Erweitert!", Toast.LENGTH_LONG).show();
            } else {
                Toast.makeText(HomeActivity.this, "Einfach!", Toast.LENGTH_LONG).show();
            }
        }};

    CompoundButton.OnCheckedChangeListener toggleListenerFloor = new CompoundButton.OnCheckedChangeListener() {
        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            if (isChecked) {
                //Toast.makeText(HomeActivity.this, "Oben!", Toast.LENGTH_LONG).show();
                ImageView img = (ImageView) findViewById(R.id.imageFloor);
                img.setImageResource(R.drawable.oben);
            } else {
                //Toast.makeText(HomeActivity.this, "Unten!", Toast.LENGTH_LONG).show();
                ImageView img = (ImageView) findViewById(R.id.imageFloor);
                img.setImageResource(R.drawable.unten);
            }
        }};
}
