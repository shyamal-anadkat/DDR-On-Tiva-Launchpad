import javafx.*;
import javafx.embed.swing.JFXPanel;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
public class DDRCOMPlayer {

	//***have to configure the PUTTY to generate a log file for the COM PORT***//
	public static void main(String[] args) throws FileNotFoundException {


		final String mediaFile = "C:/Users/user/Desktop/song.mp3";
		final String logFile = "C:/Users/user/Desktop/putty.log";

		final JFXPanel fxPanel = new JFXPanel();
		final Media media = new Media(new File(mediaFile).toURI().toString());
		MediaPlayer mediaPlayer = new MediaPlayer(media);
		int numXs = 0;
		boolean isPlaying = false;
		boolean running = true;

		BufferedInputStream reader = new BufferedInputStream(new FileInputStream(logFile));

		while (running) {
			try {
				if (reader.available() > 0) {
					char printOut = (char)reader.read();
					//X for PLAY
					if (printOut == 'X') {
						numXs ++;
						if(numXs == 1 || !isPlaying) {
							mediaPlayer.play();
							isPlaying = true;
						}	
					}
					//Z for STOP
					if (printOut == 'Z' && isPlaying) {
						mediaPlayer.stop();
						isPlaying = false;
					}
					//print out to console
					System.out.print(printOut);

				} else {
					try {
						for (int i = 0; i < 200; i++) {};
					} catch (Exception ex) {
						running = false;
					}
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}