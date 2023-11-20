import java.io.*;
import java.net.*;

        // OutputStream ostream = sock.getOutputStream(); 
        // InputStream istream = sock.getInputStream(); 
class clientrpc
{
    public static void main(String[] args) throws Exception
    {
        Socket sock = new Socket("127.0.0.1", 3000); 
        BufferedReader keyRead = new BufferedReader(new InputStreamReader(System.in)); 
        PrintWriter pwrite = new PrintWriter(sock.getOutputStream(), true); 
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(sock.getInputStream()));   
        
        System.out.println("Client ready, type and press Enter key");
        String receiveMessage, sendMessage,temp; 

        while(true) 
        {
            System.out.println("\nEnter operation to perform(add,sub,mul,div)....");
            temp = keyRead.readLine();
            sendMessage=temp.toLowerCase(); 
            pwrite.println(sendMessage);
            System.out.println("Enter first parameter :");
            sendMessage = keyRead.readLine(); 
            pwrite.println(sendMessage);
            System.out.println("Enter second parameter : ");
            sendMessage = keyRead.readLine(); 
            pwrite.println(sendMessage);
            System.out.flush(); 
            if((receiveMessage = receiveRead.readLine()) != null) 
            System.out.println(receiveMessage); 
        }
    }
}

