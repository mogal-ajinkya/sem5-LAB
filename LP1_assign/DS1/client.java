
import java.net.*;
import java.util.Scanner;
import java.io.*;

class client {
    private Socket clientSocket = null;
    private Scanner input = new Scanner(System.in);
    private DataOutputStream out = null;

    public client(String address, int port){
        try{
            clientSocket = new Socket(address, port);
            System.out.println("Connected at port number : " + port);
            out = new DataOutputStream(clientSocket.getOutputStream());

        }
        catch(UnknownHostException u){
            System.out.println(u);
            return;
        }
        catch(IOException i){
            System.out.println(i);
            return;
        }

        String line = "";

        while(!line.equals("over")){
            try{
                line = input.nextLine();
                out.writeUTF(line);
            }
            catch(IOException i){
                System.out.println(i);
                return;
            }
        }

        try{
            clientSocket.close();
            input.close();
            out.close();
        }
        catch(IOException i){
            System.out.println(i);
            return;
        }
    } 
    public static void main(String[] args){
        System.out.println("hello");
        client sampClient = new client("127.0.0.1", 5000);
    }
}