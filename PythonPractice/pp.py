from dataclasses import dataclass
@dataclass
class AnimalClass:
    name: str
    habitat: str
    teeth: int = 0
    
snowman = AnimalClass('yeti', 'Himalayas', 46)