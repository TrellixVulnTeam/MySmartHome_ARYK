package com.smarthome.thorben.smarthome;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
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

public class HomeActivity extends AppCompatActivity {

    private MqttAndroidClient client;
    private TextView humid_thorben;
    private TextView temp_thorben;
    private TextView tau_thorben;

    private TextView humid_johanna;
    private TextView temp_johanna;
    private TextView tau_johanna;

    private TextView humid_livingroom;
    private TextView temp_livingroom;
    private TextView tau_livingroom;

    private TextView floor;
    private ImageView imgjohanna;
    private ImageView imgthorben;
    private ImageView imglivingroom;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);

        imgjohanna = (ImageView) findViewById(R.id.imageView9johanna);
        imgthorben = (ImageView) findViewById(R.id.imageView8thorben);
        imglivingroom = (ImageView) findViewById(R.id.imageView7livingroom);

        humid_thorben = (TextView) findViewById(R.id.textViewTemp);
        temp_thorben = (TextView) findViewById(R.id.textViewHumid);
        tau_thorben = (TextView) findViewById(R.id.textViewTau);
        floor = (TextView) findViewById(R.id.textViewFloor);

        humid_thorben.setText("0");
        temp_thorben.setText("0");
        tau_thorben.setText("0");

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

                    setSubscription("temp_outdoor");
                    setSubscription("humid_outdoor");
                    setSubscription("tau_outdoor");
                    setSubscription("kai-uwe_outdoor");

                    setSubscription("temp_thorben");
                    setSubscription("humid_thorben");
                    setSubscription("tau_thorben");
                    setSubscription("kai-uwe_thorben");

                    setSubscription("temp_johanna");
                    setSubscription("humid_johanna");
                    setSubscription("tau_johanna");
                    setSubscription("kai-uwe_johanna");

                    setSubscription("temp_livingroom");
                    setSubscription("humid_livingroom");
                    setSubscription("tau_livingroom");
                    setSubscription("kai-uwe_livingroom");
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    Toast.makeText(HomeActivity.this, "Verbinden fehlgeschlagen!", Toast.LENGTH_LONG).show();
                }
            });
        } catch (MqttException e) {
            e.printStackTrace();
        }

        client.setCallback(new MqttCallback() {
            @Override
            public void connectionLost(Throwable cause) {

            }

            @Override
            public void messageArrived(String topic, MqttMessage message) throws Exception {

                if (topic.equals("temp_thorben")) {
                    temp_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("humid_thorben")) {
                    humid_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("tau_thorben")) {
                    tau_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("kai-uwe_thorben")) {

                    if (message.getPayload().equals("RED")) {
                        imgthorben.setImageResource(R.drawable.redlight);
                        Toast.makeText(HomeActivity.this, "Empfehlung!", Toast.LENGTH_LONG).show();
                    } else if (message.getPayload().equals("YELLOW")) {
                        Toast.makeText(HomeActivity.this, "Empfehlung!", Toast.LENGTH_LONG).show();
                        imgthorben.setImageResource(R.drawable.yellowlight);
                    } else if (message.getPayload().equals("GREEN")) {
                        Toast.makeText(HomeActivity.this, "Empfehlung!", Toast.LENGTH_LONG).show();
                        imgthorben.setImageResource(R.drawable.greenlight);
                    }
                }
                if (topic.equals("temp_johanna")) {
                    //temp_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("humid_johanna")) {
                    //humid_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("tau_johanna")) {
                    //tau_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("kai-uwe_johanna")) {
                    if (new String(message.getPayload()).equals("RED")) {
                        imgjohanna.setImageResource(R.drawable.redlight);
                    } else if (new String(message.getPayload()).equals("YELLOW")) {
                        imgjohanna.setImageResource(R.drawable.yellowlight);
                    } else if (new String(message.getPayload()).equals("GREEN")) {
                        imgjohanna.setImageResource(R.drawable.greenlight);
                    }
                }

                if (topic.equals("temp_livingroom")) {
                    //temp_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("humid_livingroom")) {
                    //humid_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("tau_livingroom")) {
                    //tau_thorben.setText(new String(message.getPayload()));
                } else if (topic.equals("kai-uwe_livingroom")) {
                    if (message.getPayload().equals("RED")) {
                        imglivingroom.setImageResource(R.drawable.redlight);
                    } else if (message.getPayload().equals("YELLOW")) {
                        imglivingroom.setImageResource(R.drawable.yellowlight);
                    } else if (message.getPayload().equals("GREEN")) {
                        imglivingroom.setImageResource(R.drawable.greenlight);
                    }
                }
            }

                @Override
                public void deliveryComplete (IMqttDeliveryToken token){

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
        }
    };

    CompoundButton.OnCheckedChangeListener toggleListenerFloor = new CompoundButton.OnCheckedChangeListener() {
        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            if (isChecked) {
                //Toast.makeText(HomeActivity.this, "Oben!", Toast.LENGTH_LONG).show();
                ImageView img = (ImageView) findViewById(R.id.imageFloor);
                img.setImageResource(R.drawable.oben_besser);

                imgjohanna.setVisibility(View.VISIBLE);
                imgthorben.setVisibility(View.VISIBLE);
                imglivingroom.setVisibility(View.INVISIBLE);
            } else {
                //Toast.makeText(HomeActivity.this, "Unten!", Toast.LENGTH_LONG).show();
                ImageView img = (ImageView) findViewById(R.id.imageFloor);
                img.setImageResource(R.drawable.unten_besser);

                imgjohanna.setVisibility(View.INVISIBLE);
                imgthorben.setVisibility(View.INVISIBLE);
                imglivingroom.setVisibility(View.VISIBLE);
            }
        }
    };
}
