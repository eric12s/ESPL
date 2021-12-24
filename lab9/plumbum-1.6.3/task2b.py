import csv
import sys

def number_of_movies_per_genre_for_country(chosenCountry):
    genres = {}
    with open('IMDB.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                countryField = row["country"]
                splittedCountries = countryField.split(', ')
                genreField = row["genre"]
                splittedGenres = genreField.split(', ')
                if chosenCountry in splittedCountries:
                    for genre in splittedGenres:
                        if genres.get(genre):
                            genres[genre] += 1
                        else:
                            genres[genre] = 1
                line_count += 1                

    with open(chosenCountry + '_genre.stats', mode='w') as csv_file:
        csv_file.write(f'genre|num_of_movies\n')
        for genre in genres.items():
            csv_file.write(f'{genre[0]}|{genre[1]}\n')

if __name__=='__main__':
    chosenCountry = sys.argv[1]
    number_of_movies_per_genre_for_country(chosenCountry)
