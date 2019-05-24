import 'package:flutter/material.dart';
import 'homePage.dart';
import 'package:flutter/services.dart';
import 'package:web_socket_channel/io.dart';

void main() {
  SystemChrome.setPreferredOrientations([DeviceOrientation.portraitUp])
    .then((_) {
  runApp(MyApp());
    });
}


class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Stay Hydrated',
      theme: ThemeData(

        brightness: Brightness.dark,
      ),
      home: MyHomePage(title: 'Stay Hydrated', channel: IOWebSocketChannel.connect('ws://echo.websocket.org'),),
    );
  }
}

