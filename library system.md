## File Manager Structure
`librarian`: Contains book inventory, policies, and member data, accessible only by the librarian.
books_inventory (dir):
game_of_thrones.txt → contain:
title
autor
number of borrowers
content

books (dir):
game_of_thrones.txt → contain:
title
autor
content

archive (dir):
move files to here

policy.txt:
ay haga

logs.txt:
logs

members data (dir):
jox.txt:
username: jox
join date: 
number of borrowed books


`/members`: Contains borrowing history and member-specific data.
member_name(dir):
borrowing_history.txt:
(username) borrowed the book (game of thrones) in: 14-2-2024
borrowed_books (dir)
games of thrones.txt

account_details.txt


`/visitors`: Contains book catalog information accessible to all visitors

book catalog:
all titles of books, choose a book to read its content

## permissions
`/librarian`
ownership → librarian:librarian
`/librarian` → others: x
`/librarian/books` → others: r
`/librarian/logs.txt` → others: w
`/librarian/members_data` → others: x
`/librarian/members data/{member_name}`: <mark style="background: #FF5582A6;">(in c)</mark>
ownership → username:librararian
permissions → others: -


`/members`
ownership → librarian:members
`/members` → others: -
`/members/{member_name}`: <mark style="background: #FF5582A6;">(in c)</mark>
ownership → username:librararian
permissions → others: -

`visitors`
ownership → librarian:librarian
access to everyone

```
# change ownership
sudo chown -R jox:librarian librarian/
sudo chown -R jox:members members/
sudo chown -R jox:librarian visitors/

# /librarian: others can execute only
sudo chmod o=x librarian/

# /librarian/books: others can read
sudo chmod o=rx librarian/books/

# /librarian/logs.txt: others can write
sudo chmod o=w librarian/logs.txt

# /librarian/members_data: others can execute only
sudo chmod o=x librarian/members_data/

# /members: no access for others
sudo chmod o= members/

# /visitors: access to everyone
sudo chmod -R 777 visitors/


# add yourself to the groups
sudo usermod -aG librarian nahmsec
sudo usermod -aG members nahmsec
```


## Librarian menu
 Manages book records, member data, and library policies.
 
1. List files/dirs in /librarian  
2. Change permissions  
3. Create file/dir  
4. Delete file/dir  
5. Create symbolic link  
6. Move old books to archive  
7. Copy file/dir  
8. Create alias  
9. Search for book or member record  
10. Add book  
11. Remove book  
12. Check books catalog  
13. Update library policies

## member menu
Borrow books and view their borrowing history

1. List files/dirs in your directory  
2. Create file/dir  
3. Delete file/dir  
4. Copy file/dir  
5. Create alias  
6. View a book  
7. Borrow a book  
8. View your borrowing history  
9. Update your borrowing history  


## Visitor menu
1. list files in /vistors
2. browse available books (see content)
3. search for books tiles
4. check book catalog
