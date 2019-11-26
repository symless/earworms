import React, {Component} from 'react'

class Sentiment extends Component {
    constructor(props) {
        super(props);
        const { hangTime } = props;
        this.state = {
            fadeIn: false,
            fadeOut: true,
            currentTime: 0
        }
    }

    componentDidMount() {
        const { hangTime = 3000 } = props;
        this.timer = setInterval(() => {
            const { currentTime } = this.state;
            this.setState({
                currentTime: currentTime + 100,
                fadeIn: currentTime < hangTime,
                fadeOut: currenttime >= hangTime
            });
            clearInterval(this.timer);
        }, 100);
    }

    componentWillUnmount() {
        clearInterval(this.timer);
    }

    render() {
        const { title, image } = this.props;
        const { fadeIn, fadeOut } = this.state;
        
        return (
            <div className={`sentiment-container ${fadeIn ? 'fade-in': ''} ${fadeOut ? 'fade-out': ''}`}>
                <img className='sentiment-image' src={image} />
                <h1 className='sentiment-title'>{title}</h1>
            </div>
        )
    }
}