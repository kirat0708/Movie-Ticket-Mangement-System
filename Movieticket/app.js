const seatStatus = Array(5).fill().map(() => Array(10).fill(1)); // 1 = available, 0 = reserved
const customerDetails = {};

function generateSeats() {
    const seatsContainer = document.querySelector('.seats');
    seatsContainer.innerHTML = '';
    for (let row = 0; row < 5; row++) {
        for (let seat = 0; seat < 10; seat++) {
            const seatElement = document.createElement('div');
            seatElement.classList.add('seat');
            seatElement.textContent = seat + 1;
            if (seatStatus[row][seat] === 0) {
                seatElement.classList.add('reserved');
            }
            seatElement.onclick = () => selectSeat(row, seat);
            seatsContainer.appendChild(seatElement);
        }
    }
}

function selectSeat(row, seat) {
    if (seatStatus[row][seat] === 1) {
        const seatElement = document.querySelectorAll('.seat')[row * 10 + seat];
        seatElement.classList.toggle('selected');
    }
}

function getSelectedSeat() {
    const row = parseInt(document.getElementById('row').value) - 1;
    const seat = parseInt(document.getElementById('seat').value) - 1;
    return { row, seat };
}

function reserveSeat() {
    const { row, seat } = getSelectedSeat();
    if (seatStatus[row][seat] === 1) {
        seatStatus[row][seat] = 0;
        const name = document.getElementById('name').value;
        const age = document.getElementById('age').value;
        const phone = document.getElementById('phone').value;
        customerDetails[`${row}-${seat}`] = { name, age, phone };
        document.getElementById('status').textContent = `Seat ${seat + 1} in Row ${row + 1} reserved successfully!`;
    } else {
        document.getElementById('status').textContent = `Sorry, the seat is already reserved.`;
    }
    generateSeats();
}

function cancelReservation() {
    const { row, seat } = getSelectedSeat();
    if (seatStatus[row][seat] === 0) {
        seatStatus[row][seat] = 1;
        delete customerDetails[`${row}-${seat}`];
        document.getElementById('status').textContent = `Reservation for seat ${seat + 1} in Row ${row + 1} canceled.`;
    } else {
        document.getElementById('status').textContent = `No reservation found for this seat.`;
    }
    generateSeats();
}

function updateReservation() {
    const { row, seat } = getSelectedSeat();
    if (seatStatus[row][seat] === 0) {
        const newRow = prompt("Enter new row (1-5):");
        const newSeat = prompt("Enter new seat number (1-10):");
        const newRowIndex = parseInt(newRow) - 1;
        const newSeatIndex = parseInt(newSeat) - 1;
        
        if (seatStatus[newRowIndex][newSeatIndex] === 1) {
            seatStatus[row][seat] = 1;
            customerDetails[`${row}-${seat}`] = null;
            seatStatus[newRowIndex][newSeatIndex] = 0;
            customerDetails[`${newRowIndex}-${newSeatIndex}`] = customerDetails[`${row}-${seat}`];
            document.getElementById('status').textContent = `Reservation moved to Row ${newRowIndex + 1}, Seat ${newSeatIndex + 1}.`;
        } else {
            document.getElementById('status').textContent = `New seat is already reserved.`;
        }
    } else {
        document.getElementById('status').textContent = `No reservation found for this seat.`;
    }
    generateSeats();
}

generateSeats();
