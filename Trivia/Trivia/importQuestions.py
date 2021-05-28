import requests
import sqlite3
import random

questions_url = "https://opentdb.com/api.php?amount=10&type=multiple"
http_success = 200
apostrophe = "&#039;"
quot = "&quot;"


def replace_http_signs(http):
    http = http.replace(apostrophe, "'")
    http = http.replace(quot, '"')
    return http


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


def main():
    questions = import_questions()
    print(questions)


if __name__ == "__main__":
    main()
