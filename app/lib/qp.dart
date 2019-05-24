import 'package:flutter/material.dart';
import 'util.dart';
import 'package:web_socket_channel/web_socket_channel.dart';

class QuestionPage extends StatefulWidget {
  QuestionPage({Key key, this.title, this.channel}) : super(key: key);

  final String title;
  final WebSocketChannel channel;

  @override
  _MyQuestionPageState createState() => _MyQuestionPageState();
}

class _MyQuestionPageState extends State<QuestionPage> {
  bool _isButtonDisabled = false;
  var currentQuestion = 'Question Loading';

    initState() {
    checkForNewAnswers();
  }
  
  void checkForNewAnswers() {
    this.widget.channel.stream.listen((message) {
      setState((){
      currentQuestion = message.toString();
      _isButtonDisabled = false;
      });
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
        child:  Text(
                this.currentQuestion ,
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
                  : () {
                      this.widget.channel.sink.add('RED');
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
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
                  : () {
                      this.widget.channel.sink.add('BLUE');
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
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
                  : () {
                      this.widget.channel.sink.add('GREEN');
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
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
                  : () {
                      this.widget.channel.sink.add('YELLOW');
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
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
                  : () {
                      this.widget.channel.sink.add('PURPLE');
                      setState(() => _isButtonDisabled = !_isButtonDisabled);
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
