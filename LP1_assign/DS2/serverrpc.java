import java.io.*;
import java.net.*;
// ServerSocket ==>  (serverside) wait for client and accepts connection socket object is created
// Socket == > 
class serverrpc
{ 
        // OutputStream ostream = sock.getOutputStream(); 
        // InputStream istream = sock.getInputStream(); 
    public static void main(String[] args) throws Exception 
    { 
        ServerSocket sersock = new ServerSocket(3000); 
        System.out.println("Server ready"); 
        Socket sock = sersock.accept( ); 
        PrintWriter pwrite = new PrintWriter(sock.getOutputStream(), true);  
        BufferedReader receiveRead = new BufferedReader(new InputStreamReader(sock.getInputStream()));


        String receiveMessage, sendMessage,fun;
        int a,b,c;
        while(true) 
        {
            fun = receiveRead.readLine();

            if(fun != null) 
                System.out.println("Operation : "+ fun);

            a = Integer.parseInt(receiveRead.readLine());
            System.out.println("Parameter 1 : "+ a);
            b = Integer.parseInt(receiveRead.readLine());
            System.out.println("Parameter 2 : "+ b);

            if(fun.compareTo("add")==0)
            {
                c=a+b;
                System.out.println("Addition = "+c);
                pwrite.println("Addition = "+c); 
            }
            else if(fun.compareTo("sub")==0)
            {
                c=a-b;
                System.out.println("Substraction = "+c);
                pwrite.println("Substraction = "+c); 
            }
            else if(fun.compareTo("mul")==0)
            {
                c=a*b;
                System.out.println("Multiplication = "+c);
                pwrite.println("Multiplication = "+c); 
            }
            else if(fun.compareTo("div")==0)
            {
                c=a/b;
                System.out.println("Division = "+c);
                pwrite.println("Division = "+c); 
            }
            System.out.flush();
        } 
    } 
}