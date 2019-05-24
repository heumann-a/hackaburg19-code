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
        child: StreamBuilder(
          stream: widget.channel.stream,
          builder: (context, snapshot) {
            return Padding(
              padding: const EdgeInsets.symmetric(vertical: 24.0),
              child: Text(
                snapshot.hasData ? '${snapshot.data}' : 'Enter a Question',
                textAlign: TextAlign.center,
                style: TextStyle(
                    color: Colors.black,
                    fontSize: screenAwareSize(35, context),
                    fontFamily: "Roboto"),
              ),
            );
          },
        ));

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
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              /*  interaction  */
              onPressed: () {
                this.widget.channel.sink.add('RED');
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
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              /*  interaction  */
              onPressed: () {
                this.widget.channel.sink.add('BLUE');
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
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              /*  interaction  */
              onPressed: () {
                this.widget.channel.sink.add('GREEN');
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
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              /*  interaction  */
              onPressed: () {
                this.widget.channel.sink.add('YELLOW');
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
              minWidth: screenAwareSize(300, context),
              height: screenAwareSize(75, context),
              /*  interaction  */
              onPressed: () {
                this.widget.channel.sink.add('PURPLE');
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
