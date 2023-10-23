

import java.net.*;
import java.io.*;

public class server {
   
    private Socket connectionSocket = null;
    private ServerSocket welcomeSocket = null;
    private DataInputStream  in = null;

    public server(int port){
        try{
            welcomeSocket = new ServerSocket(port);
            System.out.println("Server Started");

            System.out.println("Waiting for a client");

            connectionSocket = welcomeSocket.accept();
            System.out.println("Connection accepted");

            in  = new DataInputStream(new BufferedInputStream(connectionSocket.getInputStream()));
            String input = "";

            while(!input.equals("over")){
                try{
                    input = in.readUTF();
                    System.out.println("Input is : " + input);
                }
                catch(IOException i){
                    System.out.println(i);
                }
            }
            System.out.println("Closing connection");

            connectionSocket.close();
            in.close();
        }
        catch(IOException i){
            System.out.println(i);
        }
    }
    public static void main(String [] args){
        server sampServer = new server(5000);
    }
}