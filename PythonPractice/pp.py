class A():
    count = 0
    def __init__(self):
        A.count += 1
    def exclaim(self):
        print("I'm an A!")
    @classmethod
    def kids(cls):
        print("A has", cls.count, "little objects.")

easy_a = A()
breezy_a = A()
wheezy_a = A()
A.kids()

class CoyoteWeapon():
    @staticmethod
    def commercial():
        print("This CoyoteWeapon has been brought to you by Acme")
        
CoyoteWeapon.commercial()

class Quote():
    def __init__(self, person, words):
        self.person = person
        self.words = words
    def who(self):
        return self.person
    def says(self):
        return self.words + '.'

class QuestionQuote(Quote)
    def says(self):
        return self.words + '?'
    
class ExclamationQuote(Quote):
    def says(self):
        return self.words + '!'