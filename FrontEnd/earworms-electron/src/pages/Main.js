import React, {Component} from 'react';
import './Main.css';
const electron = window.require('electron');
// const fs = electron.remote.require('fs');
const ipcRenderer  = electron.ipcRenderer;

class Main extends Component{
  constructor(props){
    super(props);
    this.state = {
      currentSong: {
        artist: "",
        id: 0,
        name: "",
        length: 0,
        position: 0,
        art: "",
      },
      nextSong: {
        artist: "Hello",
        id: 0,
        name: "Bye",
        length: 0,
        position: 0,
        art: "",
      },
      progress: "1%",
      currentVote: {
        bad: 0,
        good: 0,
        neutral: 0,
        songid: 0,
      }
    }

    ipcRenderer.on('currentSong', (event, arg) => {
      this.state.currentSong = arg
      this.setState({currentSong : this.state.currentSong})

      /// get Progress
      var newVar = Math.ceil((this.state.currentSong.position/this.state.currentSong.length) * 100) + "%";
      this.setState({progress: newVar})
    })

    ipcRenderer.on('nextSong', (event, arg) => {
      this.state.nextSong = arg;
      this.setState({nextSong: this.state.nextSong})
    })

    ipcRenderer.on('voteStatus', (event, arg) => {
      console.log("received vote status!");
      this.state.currentVote = arg;
      console.log(this.state.currentVote)
      this.setState({currentVote: this.state.currentVote});
    })
  }



  downVote = () => {
    ipcRenderer.send('sending_vote', -1);
  }

  upVote = () => {
    ipcRenderer.send('sending_vote', 1);
  }

  getTime = (x) => {
    if (x === null){
      return "0:00"
    }else{
      //// set the time to timer
      var minute = x / 60;
      var second = x % 60;
      return Math.floor(minute) + ":" + Math.floor(second)
    }
  }

  getColor(){
    var curColor = "0,0,0,";
    if (this.state.currentVote.bad < this.state.currentVote.good){
      curColor = "255,0,0,";
    }
    if (this.state.currentVote.good < this.state.currentVote. bad){
      curColor = "0,0,255,";
    }
    var likedRatio = 0
    if (this.state.currentVote.good != 0){
       likedRatio = this.state.currentVote.bad / (this.state.currentVote.good + this.state.currentVote.bad);
    }
    console.log("liked ratio", likedRatio);
    var opacity = Math.abs(likedRatio - 0.5) / 0.5 // 1 if 0 or 1, 0 if 0.5

    console.log("opacity", opacity);
    console.log("opacity String", opacity.toString());
    curColor += opacity.toString();
    //// curColor should have x,x,x,x

    return curColor
  }

  //// #15 going to create a color change overlay!
	render(){
    return(
      <div className = "displayMain">
        <div className = "colorOverlay" style={{'backgroundColor': 'rgba('+ this.getColor() +')' }}>
        <script>
          window.require = require
        </script>
        <img className = "albumImage" src = {this.state.currentSong.art} />
        <div className = "timer">
          <div className = "progressBar">
              <div className = "progress" style={{width: this.state.progress}}></div>
          </div>
          <div className = "timeProgress">
            <div className = "startTime">
              {this.getTime(this.state.currentSong.position)}
            </div>
            <div className = "endTime">
              {this.getTime(this.state.currentSong.length)}
            </div>
          </div>
          
        </div>
        <div className = "bodyMain">
            <div className = "songDetailHolderMain">
              <div className = "songTitleMain">
                {this.state.currentSong.name}
              </div>
              <div className = "songArtistMain">
                {this.state.currentSong.artist}
              </div>
            </div>
            <div className = "buttonHolderMain">
              <button onClick={this.downVote}>
                <img className = "buttonImg downVote" src = {process.env.PUBLIC_URL + "/thumbs_down.png"}/>
              </button>
              <button>
                <img className = "buttonImg pause-image" src = {process.env.PUBLIC_URL + "/pause.png"}/>
              </button>
              <button onClick={this.upVote}>
                <img className = "buttonImg upVote" src = {process.env.PUBLIC_URL + "/thumbs_up.png"}/>
              </button>
            </div>
            <div className = "nextSongHolder">
              <div className = "nextLabel">
                NEXT
              </div>
              <div className = "nextTitle">
                {this.state.nextSong.name}
              </div>
              <div className = "nextArtist">
                {this.state.nextSong.artist}
              </div>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default Main;