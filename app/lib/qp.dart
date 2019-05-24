import 'package:flutter/material.dart';
import 'util.dart';

class QuestionPage extends StatefulWidget {
  QuestionPage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyQuestionPageState createState() => _MyQuestionPageState();
}

class _MyQuestionPageState extends State<QuestionPage> {
  @override
  Widget build(BuildContext context) {
    var questionContainer = new Container(
      margin: EdgeInsets.all(10.0),
      padding: EdgeInsets.all(1.0),
      // width: 300,
      height: screenAwareSize(200, context),
      decoration: BoxDecoration(
        color: Colors.white,
        border: Border.all(),
      ),
      child: Text(
        "Question here!",
        textAlign: TextAlign.center,
        style: TextStyle(
          color: Colors.black,
          fontSize: screenAwareSize(40, context), 
          fontFamily: "Roboto"),
      ),
    );

    return new Scaffold(
      // appBar: new AppBar(
      //   title: new Text("Stay Hydrated"),
      // ),
      body: new ListView(
        children: <Widget>[
          questionContainer,
        ],
      ),
    );
  }
}
