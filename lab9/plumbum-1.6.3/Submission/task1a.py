import csv

def calculate_movies_per_country():
    countries = {}
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
                    if countries.get(country):
                        countries[country] += 1
                    else:
                        countries[country] = 1
                line_count += 1
    
    with open('movies.stats', mode='w') as csv_file:
        csv_file.write(f'country_name|number_of_movies\n')
        for country in countries.items():
            csv_file.write(f'{country[0]}|{country[1]}\n')

if __name__=='__main__':
    calculate_movies_per_country()
