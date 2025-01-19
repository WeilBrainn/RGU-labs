#!/bin/bash

# Указать путь к каталогу, содержащему файлы .tex
source_directory="/home/max/Desktop/BZ/docs_latex"

# Указать путь к каталогу, куда нужно сохранить результаты (PDF)
destination_directory="/home/max/Desktop/BZ"

# Перейти в каталог с исходными файлами
cd "$source_directory"

# Найти все файлы .tex в каталоге
tex_files=$(find . -name "*.tex")

# Компиляция исходных файлов в PDF
for tex_file in $tex_files; 
do
	# Извлечение имени файла без расширения
	filename=$(basename -- "$tex_file")
	filename_noext="${filename%.*}"

	# Компиляция в PDF
	pdflatex "$tex_file"

	# Перемещение PDF файла в указанный каталог
	mv "$filename_noext.pdf" "$destination_directory/"
done

echo "PDF documentation in $destination_directory."