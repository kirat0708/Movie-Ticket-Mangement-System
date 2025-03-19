#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#else
    #include <unistd.h>
#endif

using namespace std;

class Seats {
private:
    int Seat[5][10];

public:
    Seats() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                Seat[i][j] = 1;
            }
        }
    }

    int getSeatStatus(int row, int seatNumber) {
        if (row < 1 || row > 5 || seatNumber < 1 || seatNumber > 10) {
            return -1;
        }
        return Seat[row - 1][seatNumber - 1];
    }

    void reserveSeat(int row, int seatNumber) {
        if (row < 1 || row > 5 || seatNumber < 1 || seatNumber > 10) {
            return;
        }
        Seat[row - 1][seatNumber - 1] = 0;
    }

    void cancelReservation(int row, int seatNumber) {
        if (row < 1 || row > 5 || seatNumber < 1 || seatNumber > 10) {
            return;
        }
        Seat[row - 1][seatNumber - 1] = 1;
    }

    void updateReservation(int oldRow, int oldSeat, int newRow, int newSeat) {
        cancelReservation(oldRow, oldSeat);
        reserveSeat(newRow, newSeat);
    }

    void display() {
        cout << "    ";
        for (int i = 0; i < 10; i++) {
            cout << " " << i + 1;
        }
        cout << endl;

        for (int row = 0; row < 5; row++) {
            cout << row + 1 << " ";
            for (int col = 0; col < 10; col++) {
                if (Seat[row][col] == 1) {
                    cout << "- ";
                } else {
                    cout << "X ";
                }
            }
            cout << "|" << endl;
        }
        cout << "-----------------------" << endl;
    }

    void collectCustomerDetails(string& name, int& age, string& phone) {
        cout << "Enter Customer Name: ";
        cin.ignore();
        getline(cin, name);
        
        cout << "Enter Customer Age: ";
        cin >> age;

        cout << "Enter Customer Phone Number: ";
        cin.ignore();
        getline(cin, phone);
    }

    void displayCustomerDetails(const string& name, int age, const string& phone) {
        cout << "Customer Name: " << name << endl;
        cout << "Customer Age: " << age << endl;
        cout << "Customer Phone Number: " << phone << endl;
    }

    void displayReservedSeats() {
        cout << "Reserved Seats: " << endl;
        for (int row = 0; row < 5; row++) {
            for (int col = 0; col < 10; col++) {
                if (Seat[row][col] == 0) {
                    cout << "Row " << row + 1 << " Seat " << col + 1 << endl;
                }
            }
        }
        cout << "-----------------------" << endl;
    }
};

int main() {
    Seats s;
    string customerName;
    int customerAge;
    string customerPhone;

    bool exit = false;
    while (!exit) {
        system("cls");
        cout << endl;
        cout << "Welcome To Movie Ticket Booking System" << endl;
        cout << "1. Reserve A Ticket" << endl;
        cout << "2. Cancel Reservation" << endl;
        cout << "3. Update Reservation" << endl;
        cout << "4. Display Reserved Seats" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter Your Choice: ";
        int val;
        cin >> val;

        if (val == 1) {
            s.display();

            int row, col;
            cout << "Enter Row (1-5): ";
            cin >> row;
            cout << "Enter Seat Number (1-10): ";
            cin >> col;

            if (row < 1 || row > 5 || col < 1 || col > 10) {
                cout << "Invalid Row or Seat Number!" << endl;
                sleep(3);
                continue;
            }

            int seatStatus = s.getSeatStatus(row, col);
            if (seatStatus == -1) {
                cout << "Invalid Row or Seat Number!" << endl;
                sleep(3);
                continue;
            }

            if (seatStatus == 0) {
                cout << "Sorry: Seat is already reserved!" << endl;
                sleep(3);
                continue;
            }

            s.collectCustomerDetails(customerName, customerAge, customerPhone);
            s.reserveSeat(row, col);

            cout << "Seat Is Reserved Successfully in Row " << row << " and Seat Number " << col << endl;
            cout << "Customer Details: " << endl;
            s.displayCustomerDetails(customerName, customerAge, customerPhone);

            sleep(3);
        } else if (val == 2) {
            int row, col;
            s.display();
            cout << "Enter Row (1-5) of the reservation to cancel: ";
            cin >> row;
            cout << "Enter Seat Number (1-10) of the reservation to cancel: ";
            cin >> col;

            if (row < 1 || row > 5 || col < 1 || col > 10 || s.getSeatStatus(row, col) == 1) {
                cout << "Invalid Reservation or Seat Already Available!" << endl;
                sleep(3);
                continue;
            }

            s.cancelReservation(row, col);
            cout << "Reservation Cancelled for Row " << row << " and Seat " << col << endl;
            sleep(3);
        } else if (val == 3) {
            int oldRow, oldCol, newRow, newCol;
            s.display();
            cout << "Enter Row (1-5) of the reservation to update: ";
            cin >> oldRow;
            cout << "Enter Seat Number (1-10) of the reservation to update: ";
            cin >> oldCol;

            if (oldRow < 1 || oldRow > 5 || oldCol < 1 || oldCol > 10 || s.getSeatStatus(oldRow, oldCol) == 1) {
                cout << "Invalid Reservation or Seat Already Available!" << endl;
                sleep(3);
                continue;
            }

            cout << "Enter New Row (1-5) to move the reservation: ";
            cin >> newRow;
            cout << "Enter New Seat Number (1-10) to move the reservation: ";
            cin >> newCol;

            if (newRow < 1 || newRow > 5 || newCol < 1 || newCol > 10 || s.getSeatStatus(newRow, newCol) == 0) {
                cout << "Invalid New Seat or Seat Already Reserved!" << endl;
                sleep(3);
                continue;
            }

            s.updateReservation(oldRow, oldCol, newRow, newCol);
            cout << "Reservation Updated from Row " << oldRow << " Seat " << oldCol << " to Row " << newRow << " Seat " << newCol << endl;
            sleep(3);
        } else if (val == 4) {
            s.displayReservedSeats();
            sleep(3);
        } else if (val == 5) {
            exit = true;
            cout << "Goodbye!" << endl;
            sleep(3);
        } else {
            cout << "Invalid Input" << endl;
            sleep(3);
        }
    }

    return 0;
}
