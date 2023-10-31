// Roll no 31252
// package assignment12;

import java.util.Scanner;
import com.mongodb.*;

public class assignment12{
    public static void main(String[] args) {
        try {
            MongoClient mongo = new MongoClient("10.10.14.50",27017);
            DB db = mongo.getDB("31252_db");
            DBCollection collection = db.getCollection("student");
            Scanner reader = new Scanner(System.in);
            while(true){
                System.out.println("1>Read Value from Collection");
                System.out.println("2>Insert Document");
                System.out.println("3>Update Document");
                System.out.println("4>Delete Document");
                System.out.println("5>Exit");
                System.out.println("Enter choice: ");
                int input = reader.nextInt();
                if(input == 5){
                    reader.close();
                    break;
                }
                else if(input == 1){
                    DBCursor cursor = collection.find();
                    while (cursor.hasNext()){
                        System.out.println(cursor.next());
                    }
                }
                else if(input == 2){
                    String Customer_id,Status;
                    int Amount;
                    System.out.println("Enter customerID:");
                    Customer_id = reader.next();
                    System.out.println("Enter amount:");
                    Amount = reader.nextInt();
                    System.out.println("Enter status(P/F/D):");
                    Status = reader.next();
                    BasicDBObject doc = new BasicDBObject();
                    doc.put("Customer_id",Customer_id);
                    doc.put("Amount",Amount);
                    doc.put("Status",Status);
                    collection.insert(doc);
                    System.out.println("1 document inserted.");
                }
                else if(input == 3){
                    String Customer_id,Status;
                    int Amount;
                    System.out.println("Enter customerID:");
                    Customer_id = reader.next();
                    System.out.println("Enter amount:");
                    Amount = reader.nextInt();
                    System.out.println("Enter new status:");
                    Status = reader.next();
                    BasicDBObject whereQuery = new BasicDBObject();
                    whereQuery.put("Customer_id",Customer_id);
                    whereQuery.put("Amount",Amount);
                    BasicDBObject doc = new BasicDBObject();
                    doc.put("Customer_id",Customer_id);
                    doc.put("Amount",Amount);
                    doc.put("Status",Status);
                    BasicDBObject updateObj = new BasicDBObject();
                    updateObj.put("$set",doc);
                    try{
                        collection.update(whereQuery,updateObj);
                    }
                    catch(Exception e){
                        System.out.println("Query not found");
                    }
                }
                else if(input == 4){
                    String Customer_id;
                    int Amount;
                    System.out.println("Enter customerID:");
                    Customer_id = reader.next();
                    System.out.println("Enter amount:");
                    Amount = reader.nextInt();
                    BasicDBObject query = new BasicDBObject();
                    query.put("Customer_id",Customer_id);
                    query.put("Amount",Amount);
                    try{
                        collection.remove(query);
                    }
                    catch(Exception e){
                        System.out.println("Query not found");
                    }
                }
            }
            mongo.close();
        } catch (Exception e) {
            System.out.println("Error in connecting...");
        }

    }
}

//
//import com.mongodb.MongoClient;
//import com.mongodb.MongoClientURI;
//import com.mongodb.client.FindIterable;
//import com.mongodb.client.MongoCollection;
//import com.mongodb.client.MongoCursor;
//import com.mongodb.client.MongoDatabase;
//import com.mongodb.client.model.Filters;
//import com.mongodb.client.model.Updates;
////import com.mongodb.*;
//import org.bson.*;
//
//class assignment12 {
//	public static void main(String[] args) {
//
//		// Create a mongo client instance
//		// For Authentication based 
//		// MongoClientURI uri = new MongoClientURI("mongodb://rohan:rohandoshi21@127.0.0.1:27017/?authSource=myDb");
//		MongoClientURI uri = new MongoClientURI("mongodb://10.10.14.50:27017");
//		MongoClient mongoClient = new MongoClient(uri);
//
//		MongoDatabase database = mongoClient.getDatabase("31252_db");
//
////		 If collection is already present gives error
////		database.createCollection("temp2");
//
//		for (String name : database.listCollectionNames()) {
//			System.out.println(name);
//		}
//
//		MongoCollection collection = database.getCollection("student");
////		Document doc = new Document("name", "Tanmya").append("age", 18);
//		
////		Document doc = new Document("name", "ankit").append("lastname","mogal").append("age", 18);
////		collection.insertOne(doc);
//		// Read
//		FindIterable itf = collection.find();
//
//		MongoCursor it = itf.iterator();
//
//		while (it.hasNext()) {
//			System.out.println(it.next());
//		}
//
//		// Create
//
//
//		// Update
////		collection.updateOne(Filters.eq("name", "Rohan"), Updates.set("age", 21));
//
//		// Delete
////		collection.deleteMany(Filters.and(Filters.eq("name", "Tanmya"), Filters.eq("age", 18)));
//
//	}
//}