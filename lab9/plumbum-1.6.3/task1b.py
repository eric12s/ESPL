import csv
import sys

def calculate_movies_for_country_after_date(chosenCountry, chosenDate):
    counter = 0
    with open('IMDB.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                countryField = row["country"]
                splittedCountries = countryField.split(', ')
                for country in splittedCountries:
                    if country == chosenCountry and int(row["year"]) >= chosenDate:
                        counter += 1
                line_count += 1
    print(counter)

if __name__=='__main__':
    chosenCounrty = sys.argv[1]
    chosenDate = int(sys.argv[2])
    calculate_movies_for_country_after_date(chosenCounrty, chosenDate)
