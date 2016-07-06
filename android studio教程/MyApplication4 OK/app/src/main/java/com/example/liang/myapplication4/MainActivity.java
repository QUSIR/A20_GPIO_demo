package com.example.liang.myapplication4;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    TextView textView; //声明一个标签
    Button button1; //声明一个按钮
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView)findViewById(R.id.testView); //在xml中找到标签

        button1 = (Button)findViewById(R.id.button1); //在xml中找到按钮

        button1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //点按钮以后发生的事
                Load load = new Load();
                int r = load.addInt(100, 50);
                textView.setText("C++库计算“100+50”的结果是：" + String.valueOf(r));
            }
        });

    }
}
