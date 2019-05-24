import 'package:flutter/material.dart';
import 'homePage.dart';
import 'qp.dart';

void main() => runApp(MyApp());

class MyApp extends StatelessWidget {
  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Stay Hydrated',
      theme: ThemeData(

        brightness: Brightness.dark,
      ),
      // home: MyHomePage(title: 'Stay Hydrated'),
      home: QuestionPage(title: 'Stuff'),
    );
  }
}

