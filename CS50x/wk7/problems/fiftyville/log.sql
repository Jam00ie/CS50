-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Testing structure of crime_scene_reports
SELECT * FROM crime_scene_reports;

-- Searching in crime_scene_reports for theft taken place that matches clue.
SELECT description
FROM crime_scene_reports AS csr
WHERE year = 2021
AND month = 7
AND day = 28
AND street = 'Humphrey Street' ;
-- Crime took place 10:15am, Humphrey Street bakery, and there were three witnesses.

-- Searching in interviews for witnesses mentioning the bakery taken during the crime date.
SELECT name, transcript
FROM interviews AS i
WHERE transcript LIKE '%bakery%'
AND year = 2021
AND month = 7
AND day = 28 ;
-- Between 10:15am and 10:25am, check bakery_security_logs for cars that left parking lot.
-- Bakery owner's name is Emma.
-- 2021/07/28 morning, Legget Street, theif withdraws money from the ATM.
-- Between 10:15am and 10:25am, theif calls for less than a minute
-- Theif took earliest flight out Fiftyville
-- Person on the other end purchases flight ticket

-- Searching in bakery_security_logs for cars that left parking lot
SELECT minute, activity, license_plate
FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25;

-- Searching in atm_transactions
SELECT account_number, amount
FROM atm_transactions
WHERE year = 2021
AND month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw' ;

-- Searching in phone_calls
SELECT caller, receiver
FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60 ;

-- Searching in airports for airport abbreviation
SELECT * FROM airports WHERE city = 'Fiftyville' ;
-- CSF, Fiftyville Regional Airport

-- Searching in flights for first flight
SELECT *
FROM flights
WHERE origin_airport_id IN (
    SELECT id
    FROM airports
    WHERE city = 'Fiftyville'
)
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1;
-- Theif took the 8:20am flight to LGA, LaGuardia Airport which is New York City
-- flight_id for this flight is 36
SELECT * FROM passengers
WHERE flight_id = 36;

-- Combine all clues!
SELECT * FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
);
-- Bruce is the theif
-- and the accomplice...
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND duration < 60
    AND caller IN (
        SELECT phone_number
        FROM people
        WHERE id = 686048
    )
);
-- ... is Robin.