import java.io.*;
import java.net.*;
import java.nio.*;
import java.util.*;

class UDPStopAndWaitClient{
    private static final int BUFFER_SIZE = 1024;
    private static final int PORT = 4002;
    private static final String HOSTNAME = "localhost";
    private static final int BASE_SEQUENCE_NUMBER = 1;

    public static void main(String args[]) throws Exception{
        // Create a socket
        DatagramSocket socket = new DatagramSocket();
        socket.setSoTimeout(1000);

        // The message we're going to send converted to bytes
        Integer sequenceNumber = BASE_SEQUENCE_NUMBER;


        while (true) {
            boolean timedOut = true;
			boolean ACK = false;
 
            while( timedOut ) {
                Thread.sleep(1000);
                sequenceNumber++;

                // Create a byte array for sending and receiving data
                byte[] sendData = new byte[ BUFFER_SIZE ];
                byte[] receiveData = new byte[ BUFFER_SIZE ];

                // Get the IP address of the server
                InetAddress IPAddress = InetAddress.getByName( HOSTNAME );

                System.out.println( "Sending Packet : " + sequenceNumber);                
                // Get byte data for message 
                sendData = ByteBuffer.allocate(4).putInt( sequenceNumber ).array();
				
				Random random = new Random( );
            	int chance = random.nextInt(10);
				
				if(chance != 0) {
                try {
	
                    // Send the UDP Packet to the server
                    DatagramPacket packet = new DatagramPacket(sendData, sendData.length, IPAddress, 4002);
                    socket.send( packet );

                    // Receive the server's packet
                    DatagramPacket received = new DatagramPacket(receiveData, receiveData.length);
                    socket.receive( received );
                    
                    // Get the message from the server's packet
                    int returnMessage = ByteBuffer.wrap( received.getData( ) ).getInt();

                    System.out.println( "ACK Received : " + returnMessage );
                    // If we receive an ack, stop the while loop
					timedOut = false;
                } catch ( SocketTimeoutException exception ){
                    // If we don't get an ack, prepare to resend sequence number
                    System.out.println( "No ACK recieved on : " + sequenceNumber + "   Resending..." );
                    sequenceNumber--;
                }
				}
				else{
					System.out.println( "Data Packet lost on: " + sequenceNumber + "   Resending..." );
					sequenceNumber--;
				}
            }    
        }
    }
}
