import requests
import random
import sqlite3
from sqlite3 import Error
import re

questions_url = "https://opentdb.com/api.php?amount=10&type=multiple"
http_success = 200
apostrophe = "&#039;"
quot = "&quot;"
A, B, C, D = 0, 1, 2, 3


def replace_http_signs(http_str):
    http_str = http_str.replace(apostrophe, '"')
    http_str = http_str.replace(quot, '"')

    return http_str


def extract_question_details(question_data):
    # extract parameters from data and remove http characters using replace
    question = replace_http_signs(question_data["question"])
    correct_answer = question_data["correct_answer"]
    incorrect_answers = question_data["incorrect_answers"]

    answers = [replace_http_signs(correct_answer),
               replace_http_signs(incorrect_answers[0]),
               replace_http_signs(incorrect_answers[1]),
               replace_http_signs(incorrect_answers[2])]

    random.shuffle(answers)

    return {"question": question,
            "answers": answers,
            "correct_answer": correct_answer}


def extract_questions(questions):
    questions_array = []

    for question in questions:
        question_details = extract_question_details(question)
        questions_array.append(question_details)

    return questions_array


def import_questions():
    data = requests.get(questions_url)

    if data.status_code == http_success:
        data = data.json()
        return extract_questions(data["results"])


def sql_connection():
    try:
        db = sqlite3.connect('Trivia.db')
        print("Connection is established: Database is created in memory")

    except Error:
        print(Error)

    return db


def execute_command(db, create_table_sql):
    try:
        sql = db.cursor()
        sql.execute(create_table_sql)

    except Error as error:
        print(error)

    db.commit()

    return sql.lastrowid


def create_question_table(db):
    sql_create_question_table = """CREATE TABLE IF NOT EXISTS questions (
                                    id	INTEGER,
                                    question	TEXT NOT NULL,
                                    A	TEXT NOT NULL,
                                    B	TEXT NOT NULL,
                                    C	TEXT NOT NULL,
                                    D	TEXT NOT NULL,
                                    correct_answer	TEXT NOT NULL,
                                    PRIMARY KEY(id AUTOINCREMENT)
                                    );"""

    execute_command(db, sql_create_question_table)


def insert_questions_to_table(db, questions):
    sql_insert_to_table = """INSERT INTO questions
                            (question, A, B, C, D, correct_answer)
                            VALUES('{0}', '{1}', '{2}', '{3}', '{4}', '{5}');"""

    for question_details in questions:
        sql_formatted_command = sql_insert_to_table.format(
            question_details["question"],
            question_details["answers"][A],
            question_details["answers"][B],
            question_details["answers"][C],
            question_details["answers"][D],
            question_details["correct_answer"])

        execute_command(db, sql_formatted_command)


def clear_table(db):
    sql_command = 'DELETE FROM questions'

    sql = db.cursor()
    sql.execute(sql_command)
    db.commit()


def main():
    questions = import_questions()

    db = sql_connection()
    create_question_table(db)
    clear_table(db)
    insert_questions_to_table(db, questions)

    db.close()


if __name__ == "__main__":
    main()
