package com.smarthome.thorben.mysmarthome;

import android.os.Bundle;
import android.speech.tts.TextToSpeech;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
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

import java.io.UnsupportedEncodingException;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements TextToSpeech.OnInitListener, View.OnClickListener {

    private TextToSpeech tts;
    private MqttAndroidClient client;
    private TextView humid;
    private TextView temp;
    private TextView tau;
    private TextView advice;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tts = new TextToSpeech(this,this);

        humid = (TextView) findViewById(R.id.textView7);
        temp = (TextView) findViewById(R.id.textView6);
        tau = (TextView) findViewById(R.id.textView11);
        advice = (TextView) findViewById(R.id.textView8);

        String clientId = MqttClient.generateClientId();
        client =
                new MqttAndroidClient(this.getApplicationContext(), "tcp://192.168.178.102:1883",
                        clientId);

        try {
            IMqttToken token;
            token = client.connect();
            token.setActionCallback(new IMqttActionListener() {
                @Override
                public void onSuccess(IMqttToken asyncActionToken) {
                    // We are connected
                    Toast.makeText(MainActivity.this,"connected!",Toast.LENGTH_LONG).show();

                    setSubscription("temp_thorben");
                    setSubscription("humid_thorben");
                    setSubscription("tau_thorben");
                    setSubscription("air_thorben");

                    ToggleButton toggle_mode = (ToggleButton) findViewById(R.id.toggleButton2);
                    toggle_mode.setOnCheckedChangeListener(toggleListener);
                }

                @Override
                public void onFailure(IMqttToken asyncActionToken, Throwable exception) {
                    // Something went wrong e.g. connection timeout or firewall problems
                    Toast.makeText(MainActivity.this,"failed to connect!",Toast.LENGTH_LONG).show();
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

                if(topic.equals("temp_thorben")){
                    temp.setText(new String(message.getPayload()));
                }else if(topic.equals("humid_thorben")){
                    humid.setText(new String(message.getPayload()));
                }else if(topic.equals("tau_thorben")){
                    tau.setText(new String(message.getPayload()));
                } else if(topic.equals("air_thorben")){
                    advice.setText(new String(message.getPayload()));
                }
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {

            }
        });

    }

    CompoundButton.OnCheckedChangeListener toggleListener = new CompoundButton.OnCheckedChangeListener() {

        public void onCheckedChanged(CompoundButton v, boolean isChecked) {
            String topic = "mode_led";
            String payload = "T";

            byte[] encodedPayload = new byte[0];

            if (isChecked) {
                tts.speak("Ab jetzt werden Nachrichten auf der LED-Box angezeigt!", TextToSpeech.QUEUE_FLUSH, null);
                try {
                    payload = "S";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }

            } else {
                tts.speak("Ab jetzt wird die Uhrzeit auf der LED-Box angezeigt!", TextToSpeech.QUEUE_FLUSH, null);
                try {
                    payload = "T";
                    encodedPayload = payload.getBytes("UTF-8");
                    MqttMessage message = new MqttMessage(encodedPayload);
                    message.setRetained(true);
                    client.publish(topic, message);
                } catch (UnsupportedEncodingException | MqttException e) {
                    e.printStackTrace();
                }
            }
        }};


    @Override
    public void onInit(int status) {
        tts.setLanguage(Locale.GERMAN);
        Button button = (Button) findViewById(R.id.button);
        button.setOnClickListener(this);
    }

    @Override
    public void onClick(View v){
        EditText editText = (EditText) findViewById(R.id.editText);

        String topic = "msg_led";
        String payload = editText.getText().toString();
        byte[] encodedPayload = new byte[0];

        tts.speak(payload,TextToSpeech.QUEUE_FLUSH,null);

        try {
            encodedPayload = payload.getBytes("UTF-8");
            MqttMessage message = new MqttMessage(encodedPayload);
            message.setRetained(true);
            client.publish(topic, message);
        } catch (UnsupportedEncodingException | MqttException e) {
            e.printStackTrace();
        }
    }

    private void setSubscription(String topic){
        try{
            client.subscribe(topic,0);
        }catch(MqttException e){
            e.printStackTrace();
        }
    }
}
