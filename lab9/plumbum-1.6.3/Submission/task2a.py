import csv

def total_duration_per_genre():
    genres = {}
    with open('IMDB.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                genreField = row["genre"]
                splittedGenres = genreField.split(', ')
                for genre in splittedGenres:
                    if genres.get(genre):
                        genres[genre] += int(row["duration"])
                    else:
                        genres[genre] = int(row["duration"])
                line_count += 1
    
    with open('genre.stats', mode='w') as csv_file:
        csv_file.write(f'genre|average duration\n')
        for genre in genres.items():
            csv_file.write(f'{genre[0]}|{genre[1]}\n')

if __name__=='__main__':
    total_duration_per_genre()
