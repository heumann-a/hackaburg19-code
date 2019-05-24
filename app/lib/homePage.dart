import 'package:flutter/material.dart';
import 'qp.dart';
import 'util.dart';
import 'package:web_socket_channel/web_socket_channel.dart';
import 'package:web_socket_channel/io.dart';
import 'dart:io';

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title, this.channel}) : super(key: key);

  final String title;
  final WebSocketChannel channel;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  bool isConnected = false;

  bool isChannelOpen = false;

  initState() {
    checkIfConnected();
  }

  void checkIfConnected() {
    print('function called');
    this.widget.channel.stream.listen((message) {
      print('Message: ${message.toString()}');
      setState((){
      isConnected = message.toString() == 'STATUS';
      });
    });
    
  }

  @override
  Widget build(BuildContext context) {
    return Container(
        decoration: BoxDecoration(
            gradient: LinearGradient(
                colors: [Color(0x1a000077), Color(0xFF292C36)],
                begin: Alignment.topCenter,
                end: Alignment.bottomCenter,
                tileMode: TileMode.clamp)),
        width: double.infinity,
        height: screenAwareSize(245.0, context),
        child: Stack(
          children: <Widget>[
            Container(
              child: Image.asset("assets/stay-hydrated.png",
                  height: screenAwareSize(325, context),
                  width: double.infinity,
                  fit: BoxFit.scaleDown),
            ),
            Container(
                width: screenAwareSize(400, context),
                padding: const EdgeInsets.only(bottom: 30.0),
                alignment: Alignment.bottomCenter,
                child: RaisedButton(
                  onPressed: () {
                      print('Pre channel Open: ' + isChannelOpen.toString());
                      this.widget.channel.sink.add('STATUS');

                  },
                  color: isConnected ? Colors.green : Colors.red,
                  child: Text(isConnected ? 'Connected' : 'Connect'),
                )),
            isConnected
                ? Container(
                    width: screenAwareSize(400, context),
                    padding: const EdgeInsets.only(bottom: 30.0, right: 20),
                    alignment: Alignment.bottomRight,
                    child: FloatingActionButton(
                      onPressed: () {
                        Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) =>
                                    new QuestionPage(channel: widget.channel)));
                      },
                      backgroundColor: Color(0xFF60626b),
                      child: Icon(Icons.fast_forward),
                    ))
                : Container(width: 0, height: 0),
          ],
        ));
  }
}
