import 'package:flutter/material.dart';
import 'util.dart';

class MyHomePage extends StatefulWidget {
  MyHomePage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {

  @override
  Widget build(BuildContext context) {

    return Container(
      width: double.infinity,
      height: screenAwareSize(5.0, context),
      child: Stack(children: <Widget>[
        Container(
                child: Image.asset("assets/stay-hydrated.png",
                    width: double.infinity,
                    height: double.infinity,
                    fit: BoxFit.contain),
              ),

      ],)
    );
  }
}