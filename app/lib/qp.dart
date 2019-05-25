import 'package:flutter/material.dart';
import 'util.dart';
import 'package:http/http.dart' as http;
import 'dart:io';

class QuestionPage extends StatefulWidget {
  QuestionPage({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MyQuestionPageState createState() => _MyQuestionPageState();
}

class _MyQuestionPageState extends State<QuestionPage> {
  bool _isButtonDisabled = false;
  var currentQuestion = 'Question Loading';

  initState() {
    http.get('http://192.168.4.1:80/question').then((response) {
      setState(() {
        currentQuestion = response.body;
      });
    });
  }

  Future checkForNewAnswers(String color) async {
    await http.post('http://192.168.4.1:80/answer?answer=${color}');

    var newQuestionResponse = await http.get('http://192.168.4.1:80/question');

    while(newQuestionResponse.body == currentQuestion || newQuestionResponse.body == '') {
      newQuestionResponse = await http.get('http://192.168.4.1:80/question');
       sleep(const Duration(milliseconds: 100));
    }

    setState(() {
      currentQuestion = newQuestionResponse.body;
      _isButtonDisabled = false;
    });
  }

  @override
  Widget build(BuildContext context) {
    var questionContainer = new Container(
      margin: EdgeInsets.all(10.0),
      padding: EdgeInsets.all(1.0),
      width: screenAwareSize(300, context), //we might not even need a width
      height: screenAwareSize(150, context),
      decoration: BoxDecoration(
        color: Colors.white,
        border: Border.all(),
      ),
      child: Text(
        this.currentQuestion,
        textAlign: TextAlign.center,
        style: TextStyle(
            color: Colors.black,
            fontSize: screenAwareSize(35, context),
            fontFamily: "Roboto"),
      ),
    );

    var buttonContainer = new Container(
        margin: EdgeInsets.symmetric(
          vertical: 30.0,
          horizontal: 40.0,
        ),
        height: screenAwareSize(400, context),
        decoration: BoxDecoration(
            gradient: LinearGradient(
                colors: [Color(0x1a000077), Color(0xFF292C36)],
                begin: Alignment.topCenter,
                end: Alignment.bottomCenter,
                tileMode: TileMode.clamp)),
        child: ListView(
          children: <Widget>[
            MaterialButton(
              child: Text(
                'Player 1',
                style: TextStyle(fontSize: screenAwareSize(15, context)),
              ),
              color: Colors.red,
              disabledColor: Colors.redAccent,
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(25)),
              /*  interaction  */
              onPressed: _isButtonDisabled
                  ? null
                  : () async {
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
                      await checkForNewAnswers('RED');
                    },
            ),
            const SizedBox(
              height: 20,
            ),
            MaterialButton(
              child: Text(
                'Player 2',
                style: TextStyle(fontSize: screenAwareSize(15, context)),
              ),
              color: Colors.blue,
              disabledColor: Colors.blueAccent,
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(25)),
              /*  interaction  */
              onPressed: _isButtonDisabled
                  ? null
                  : () async {
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
                      await checkForNewAnswers('BLUE');
                    },
            ),
            const SizedBox(
              height: 20,
            ),
            MaterialButton(
              child: Text(
                'Player 3',
                style: TextStyle(fontSize: screenAwareSize(15, context)),
              ),
              color: Colors.green,
              disabledColor: Colors.greenAccent,
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(25)),
              /*  interaction  */
              onPressed: _isButtonDisabled
                  ? null
                  : () async {
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
                      await checkForNewAnswers('GREEN');
                    },
            ),
            const SizedBox(
              height: 20,
            ),
            MaterialButton(
              child: Text(
                'Player 4',
                style: TextStyle(fontSize: screenAwareSize(15, context)),
              ),
              color: Colors.yellow,
              disabledColor: Colors.yellowAccent,
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(25)),
              /*  interaction  */
              onPressed: _isButtonDisabled
                  ? null
                  : () async {
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
                      await checkForNewAnswers('YELLOW');
                    },
            ),
            const SizedBox(
              height: 20,
            ),
            MaterialButton(
              child: Text(
                'Player 5',
                style: TextStyle(fontSize: screenAwareSize(15, context)),
              ),
              color: Colors.purple,
              disabledColor: Colors.purpleAccent,
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(25)),
              /*  interaction  */
              onPressed: _isButtonDisabled
                  ? null
                  : () async {
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
                      await checkForNewAnswers('PURPLE');
                    },
            )
          ],
        ));

    return new Scaffold(
      body: new ListView(
        children: <Widget>[
          questionContainer,
          buttonContainer,
        ],
      ),
    );
  }
}
