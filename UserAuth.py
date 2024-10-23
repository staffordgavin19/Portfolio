import sqlite3
import hashlib

# Connect to SQL database
conn = sqlite3.connect('UserAuth.db')
c = conn.cursor()

# Create users table
c. execute('''
     CREATE TABLE IF NOT EXISTS users (
         id INTEGER PRIMARY KEY,
         username TEXT UNIQUE,
         password TEXT
     )
''')
conn.commit()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def register(username, password):
    hashed = hash_password(password)
    try:
        c.execute('INSERT INTO users (username, password) VALUES (?, ?)', (username, hashed))
        conn.commit()
        print("User registered successfully")
    except sqlite3.IntegrityError:
        print("Username already exists")

def login(username, password):
    hashed = hash_password(password)
    c.execute('SELECT password FROM users WHERE username = ?', (username,))
    result = c.fetchone()
    if result and result[0] == hashed:
        print("Login successful!")
    else:
        print("Invalid username or password.")

def display_menu():
    print("Welcome to the User Authenticator")
    print("1. Register")
    print("2. Login")
    print("3. Exit")

def main():
    while True:
        display_menu()
        choice = input("Please choose an option (1-3): ")

        if choice == '1':
            username = input("Enter a username: ")
            password = input("Enter a password: ")
            register(username, password)
        elif choice == '2':
            username = input("Enter your username: ")
            password = input("Enter your password: ")
            login(username, password)
        elif choice == '3':
            print("Exiting the program.")
            break
        else:
            print("Invalid option. Please try again.")

if __name__ == "__main__":
    main()

# Example usage
register("testuser", "test123")
login("testuser", "test123")

conn.close()