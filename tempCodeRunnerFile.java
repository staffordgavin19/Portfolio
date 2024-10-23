import java.util.ArrayList;
import java.util.List;

public interface Observer {
    void update(String message);
}

public class NotificationService implements Observer {
    private String patronName;

    public NotificationService(String name) {
        this.patronName = name;
    }

    @Override
    public void update(String message) {
        System.out.println(patronName + " received notification: " + message);
    }
}

public class Library {
    private List<Observer> observers = new ArrayList<>();
    private List<Book> books = new ArrayList<>();

    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    public void notifyObservers(String message) {
        for (Observer observer : observers) {
            observer.update(message);
        }
    }

    public void addBook(Book book) {
        books.add(book);
        // Notify observers about the new book
        notifyObservers("New book available: " + book.getTitle());
    }

    public void changeBookAvailability(Book book, boolean isAvailable) {
        book.setAvailable(isAvailable);
        if (isAvailable) {
            notifyObservers("Book is now available: " + book.getTitle());
        }
    }
}

public class Book {
    private String title;
    private String author;
    private boolean isAvailable;

    public Book(String title, String author) {
        this.title = title;
        this.author = author;
        this.isAvailable = false; // default to not available
    }

    public String getTitle() {
        return title;
    }

    public void setAvailable(boolean available) {
        isAvailable = available;
    }

    public boolean isAvailable() {
        return isAvailable;
    }
}

public class Patron {
    private String name;
    private NotificationService notificationService;

    public Patron(String name) {
        this.name = name;
        this.notificationService = new NotificationService(name);
    }

    public NotificationService getNotificationService() {
        return notificationService;
    }
}

public class Main {
    public static void main(String[] args) {
        // Create Library
        Library library = new Library();
        
        // Create Patrons
        Patron john = new Patron("John Doe");
        Patron jane = new Patron("Jane Smith");
        
        // Register patrons for notifications
        library.addObserver(john.getNotificationService());
        library.addObserver(jane.getNotificationService());
        
        // Create Books
        Book book1 = new Book("The Great Gatsby", "F. Scott Fitzgerald");
        Book book2 = new Book("1984", "George Orwell");
        
        // Add Books to Library
        library.addBook(book1);
        library.addBook(book2);
        
        // Change Book Availability
        library.changeBookAvailability(book1, true); // Notify patrons
        library.changeBookAvailability(book2, true); // Notify patrons
    }
}