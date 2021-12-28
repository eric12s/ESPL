import csv
import matplotlib.pyplot as plt

def number_of_movies_per_year():
    years = []
    with open('IMDB.csv', mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        line_count = 0
        for row in csv_reader:
            if line_count == 0:
                line_count += 1
            else:
                years.append(row["year"])
                line_count += 1
    show_histagram(years)

def show_histagram(years):
    num_bins = len(years)
    plt.hist(years, num_bins, facecolor='blue', alpha=0.5)
    plt.xlabel('Year')
    plt.ylabel('#Movies')
    plt.title('Years histogram')
    plt.show()

if __name__=='__main__':
    number_of_movies_per_year()
