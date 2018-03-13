DATES = ['May 15',       'May 16',    'May 19',
         'June 17',     'June 18',
         'July 14',     'July 16',
         'August 14', 'August 15', 'August 17']

def Month(date): return date.split()[0]

def Day(date): return date.split()[1]

print(Month('May 15'))

print(Day('May 15'))

def tell(part, possible_dates=DATES):
    """Cheryl tells a part of her birthdate to someone;
    return a new list of possible dates that match the part."""
    return [date for date in possible_dates if part in date]

def know(possible_dates):
    """A person  knows the birthdate if they have exactly one possible
       date."""
    return len(possible_dates) == 1

print(tell('May'))
print(tell('15'))

print(know(tell('15')))

def cheryls_birthday(possible_dates=DATES):
    """Return a list of the possible dates for which statements 3 to 5 are
       true"""
    return filter(statements3to5, possible_dates)

def statements3to5(date): return statement3(date) and statement4(date) and statement5(date)

def statement3(date):
    """Albert: I don't know when Cheryl's birthday is, but I know that Bernard does not know too."""
    possible_dates = tell(Month(date))
    return (not know(possible_dates)
            and all(not know(tell(Day(d))) for d in possible_dates))

print(statement3('May 15'))

def statement4(date):
    return know(tell(Day(date), post_statement3))

post_statement3 = filter(statement3, DATES)
print('post_statement3 ', post_statement3)

#print('statement4 ', statement4('July 16', post_statement3))
#print([d for d in post_statement3 if statement3(d) and statement4(d, post_statement3)])
post_statement4 = filter(statement4, post_statement3)
print(post_statement4)

def statement5(date):
    return know(tell(Month(date), post_statement4))

post_statement5 = filter(statement5, post_statement4)
print(post_statement5)