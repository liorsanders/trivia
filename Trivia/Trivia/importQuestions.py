import requests
import sqlite3
import random

db_url = "https://opentdb.com/api.php?amount=10&type=multiple"
http_success = 200


def create_data_dict(data):
    # extract parameters from data
    question = data["question"]
    correct_answer = data["correct_answer"]
    incorrect_answers = data["incorrect_answers"]

    answers = [correct_answer,
               incorrect_answers[0],
               incorrect_answers[1],
               incorrect_answers[2]]

    random.shuffle(answers)

    return {"question": question,
            "answers": answers,
            "correct_answer": correct_answer}


def main():
    data = requests.get(db_url)

    if data.status_code == http_success:
        data = data.json()
        dict = create_data_dict(data["results"][0])
        print(dict)


if __name__ == "__main__":
    main()
