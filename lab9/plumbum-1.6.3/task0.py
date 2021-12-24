from plumbum.cmd import cat, sed, awk, wc, sort, uniq

def names(file_path):
    regex = r's/\([a-Z]*\)[\t].*/\1/g'
    command = cat[file_path] | sed[regex]
    return command()

def num_of_students(file_path):
    regex = r's/\([a-Z]*\)[\t].*/\1/g'
    command = cat[file_path] | sed[regex] | wc['-w']
    return command()

def error_code_occurrence_stats(file_path):
    regex1 = r's/[a-Z]*[\t]\(.*\)/\1/g'
    regex2 = r's/[|]/\n/g'
    regex3 = r's/[:].*//g'

    command = cat[file_path] | sed[regex1] | sed[regex2] | sed[regex3] | awk['NF'] | sort | uniq['-c']
    return command()

def number_of_error_codes(file_path):
    regex1 = r's/[a-Z]*[\t]\(.*\)/\1/g'
    regex2 = r's/[|]/\n/g'
    regex3 = r's/[:].*//g'

    command = cat[file_path] | sed[regex1] | sed[regex2] | sed[regex3] | sort | uniq | awk['NF'] | wc['-w']
    return command()

if __name__ == '__main__':
    file = 'lab10_grades'
    print(f'Students:\n{names(file)}')
    print(f'Number of students: {num_of_students(file)}')
    print(f'Errors:\n{error_code_occurrence_stats(file)}')
    print(f'Number of uniqe error codes: {number_of_error_codes(file)}')