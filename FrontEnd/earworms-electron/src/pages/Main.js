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
      progress: "1%"
    }

    ipcRenderer.on('currentSong', (event, arg) => {
      this.state.currentSong = arg
      this.setState({currentSong : this.state.currentSong})

      /// get Progress
      var newVar = Math.ceil((this.state.currentSong.position/this.state.currentSong.length) * 100) + "%";
      this.setState({progress: newVar})

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

	render(){
    return(
      <div className = "displayMain">
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
              <img className = "buttonImg" src = {process.env.PUBLIC_URL + "/thumbs_down.png"}/>
            </button>
            <button onClick={this.upVote}>
              <img className = "buttonImg" src = {process.env.PUBLIC_URL + "/thumbs_up.png"}/>
            </button>
          </div>
        </div>
      </div>
    );
  }
}

export default Main;