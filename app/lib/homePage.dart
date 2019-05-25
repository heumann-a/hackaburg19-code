import 'package:flutter/material.dart';
import 'qp.dart';
import 'util.dart';
import 'package:http/http.dart' as http;

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  bool isConnected = false;
  
  Future checkIfConnected() async {
    var response  = await http.get('http://192.168.4.1:80/connected');

    setState(() {
      isConnected = response.statusCode == 200;
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
                  onPressed: () async {
                      await checkIfConnected();
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
                                    new QuestionPage()));
                      },
                      backgroundColor: Color(0xFF60626b),
                      child: Icon(Icons.fast_forward),
                    ))
                : Container(width: 0, height: 0),
          ],
        ));
  }
}
