import java.util.concurrent.*;

public class ProducerConsumer 
{
    private static BlockingQueue<Integer> Buffer = new LinkedBlockingDeque<>();
    private static Semaphore emptySlots = new Semaphore(1);
    private static Semaphore fullSlots = new Semaphore(0);

    public static void main(String args[]) {
        Thread producerThread = new Thread(new Producer());
        Thread consumerThread = new Thread(new Consumer());

        producerThread.start();
        consumerThread.start();
    }

    static class Producer implements Runnable {
        // @Override
        public void run () {
            try {
                while(true) {
                    int item = produceItem();
                    emptySlots.acquire();
                    Buffer.put(item);
                    fullSlots.release();
                    // TimeUnit.SECONDS.sleep(1);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        private int produceItem () {
            int item = (int) (Math.random() * 100);
            System.out.println("produce : " + item);
            return item ;
        }
    }

    static class Consumer implements Runnable {
        // @Override
        public void run () {
            try {
                while(true) {
                    TimeUnit.SECONDS.sleep(1);
                    fullSlots.acquire();
                    int item = Buffer.take();
                    emptySlots.release();
                    consumeItem(item);
                }
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        private void consumeItem (int item) {
            System.out.println("Consumed: " + item);
        }
    }
}