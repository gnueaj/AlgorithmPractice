from logging import exception


class UppercaseException(Exception):
    pass # UppercaseException에 대한 행동 정의

words = ['eenie', 'meenie', 'miny', 'MO']
for word in words:
    if word.isupper():
        raise UppercaseException(word) # raise 로 예외 발생시키기
    