--ПОДГОТОВКА 2025 ------------------------------>
--12.09.2024
SELECT AVG(price)
FROM laptop
JOIN product On product.model = laptop.model
WHERE (ram >= 16 AND ram <=32) Or maker IS NULL
--> Отговор Б-> защото когато условието е в ON няма да махнем NULL редове
SELECT maker, COUNT(DISTINCT Laptop.model)
FROM Laptop
RIGHT JOIN Product
ON Laptop.model = Product.model
AND screen = 14
GROUP BY maker;

--09.07.2024
SELECT code, price, maker
FROM pc
LEFT JOIN product on product.model = pc.model
WHERE pc.model like 'A%2' OR pc.model ISNULL
--> Отговор В
SELECT maker
FROM Product p
WHERE type = ’Laptop’
AND EXISTS (SELECT *
FROM Product
WHERE type = ’PC’
AND maker = p.maker)
GROUP BY maker
HAVING COUNT(*) >= 2;

--11.09.2023
-->1
SELECT Distinct(starname)
FROM STARSIN
JOIN MOVIESTAR on STARSIN.STARNAME = MOVIESTAR.NAME
WHERE MOVIESTAR.GENDER LIKE 'F' And starname in (SELECT starname from STARSIN where movieyear <= 2000) 
And starname In (SELECT starname FROM STARSIN WHERE movieyear > 2000)

SELECT DISTINCT name 
from MOVIESTAR
JOIN STARSIN as s on name = s.STARNAME
where name in (SELECT starname from STARSIN where movieyear <= 2000 and gender = 'F') 
AND name in (SELECT starname from STARSIN where movieyear > 2000 and gender = 'F');

SELECT starname
FROM StarsIn
JOIN MovieStar ON starname = name
WHERE movieyear <= 2000 AND gender = 'F'
INTERSECT
SELECT starname
FROM StarsIn
JOIN MovieStar ON starname = name
WHERE movieyear > 2000 AND gender = 'F';
-->Отговор В
SELECT name
FROM Studio
WHERE (SELECT SUM(length)
FROM Movie
WHERE incolor = 'N'
AND studioname = Studio.name)
> (SELECT MAX(length)
FROM Movie
WHERE studioname = Studio.name);

--11.07.2023
SELECT class
FROM Classes
WHERE class NOT IN (SELECT class
FROM Ships
JOIN Outcomes ON name = ship
WHERE result = 'damaged');
--> Отговор А
SELECT class, COUNT(ship)
FROM Ships
LEFT JOIN Outcomes
ON Ships.name = Outcomes.ship
AND result = 'sunk'
GROUP BY class;

--07.09.2022
SELECT title, length
FROM MOVIE
WHERE incolor = 'Y' and length not NULL and length Not IN 
(SELECT MAX(length) FROM MOVIE WHERE incolor = 'Y')
--> Отговор В
SELECT name
FROM Studio
LEFT JOIN Movie ON name = studioname
GROUP BY name
HAVING COUNT(DISTINCT year) <= 1;

--12.07.2022
SELECT s.name, m.title
FROM MOVIE as m JOIN STUDIO s on m.STUDIONAME = s.NAME
WHERE s.NAME in (SELECT studioname FROM MOVIE WHERE title = 'The Usual Suspect' And MOVIE.YEAR = 1995)

SELECT studioname, title
from MOVIE
WHERE studioname in (SELECT studioname FROM MOVIE WHERE title LIKE 'The Usual Suspects')
--> Отговор Б
SELECT ms.name, si.movietitle
FROM moviestar ms
LEFT JOIN starsin si
ON ms.name=si.starname
WHERE si.movietitle IS NULL;

--08.09.2021
--4.1 -> В поточка
SELECT studioName
FROM Movie
WHERE inColor = 'Y'
INTERSECT
SELECT studioName
FROM Movie
WHERE length IS NULL;
-->4.2 б поточка
SELECT name, COUNT(title)
FROM MovieStar
LEFT JOIN StarsIn ON name = starName
LEFT JOIN Movie
ON movieTitle = title
AND movieYear = year
AND inColor = 'N'
WHERE gender = 'F'
GROUP BY name;

--13.07.2021
--> 1 -> а
SELECT code, price FROM Laptop
WHERE screen BETWEEN 13 AND 15
AND ram IN (SELECT ram
FROM PC);
--> 2 -> в поточка
SELECT maker, COUNT(code) FROM Laptop
RIGHT JOIN Product
ON Laptop.model = Product.model
AND screen = 15
GROUP BY maker;

--16.09.2020
-->1
SELECT DISTINCT(name), address
from STUDIO
WHERE name IN (SELECT studioname from MOVIE WHERE incolor = 'Y')
and name in (SELECT studioname from MOVIE WHERE incolor = 'N')
ORDER by address
-->2 
SELECT name, address, AVG(length)
from STUDIO
LEFT join MOVIE on STUDIO.NAME = MOVIE.STUDIONAME
GROUP by name 
HAVING COUNT(MOVIE.TITLE) <= 3

--05.08.2020
-->1
SELECT name, birthdate
FROM MOVIESTAR
WHERE name NOT LIKE '%Jr.%'
and name in (SELECT starname FROM STARSIN JOIN MOVIE on MOVIE.TITLE = STARSIN.MOVIETITLE WHERE MOVIE.INCOLOR = 'Y')
ORDER by birthdate, name
-->2
SELECT name, birthdate, COUNT(DISTINCT studioname)
from MOVIESTAR
LEFT JOIN STARSIN on MOVIESTAR.NAME = STARSIN.STARNAME
LEFT JOIN MOVIE on MOVIE.TITLE = STARSIN.MOVIETITLE AND MOVIE.YEAR = STARSIN.MOVIEYEAR
WHERE MOVIESTAR.GENDER = 'F'
GROUP by name
HAVING COUNT(MOVIE.TITLE) <= 6

--10.09.2019
--> 1 Б
SELECT ME.NAME, M.YEAR, COUNT(*) AS CNT
FROM MOVIEEXEC ME
JOIN MOVIE M
ON ME.CERT = M.PRODUCERC
GROUP BY ME.CERT, ME.NAME, M.YEAR;
-->2
SELECT name
FROM MOVIESTAR
WHERE birthdate in (SELECT MIN(birthdate) FROM MOVIESTAR)

--09.07.2019
-->C
SELECT S.NAME, COUNT(M.TITLE) as CNT
FROM STUDIO S JOIN MOVIE M
ON S.NAME = M.STUDIONAME
GROUP BY S.NAME
HAVING COUNT(M.TITLE) < 2;
-->2
SELECT name
FROM MOVIEEXEC
WHERE networth in (SELECT MIN(networth) FROM MOVIEEXEC)

--10.09.2018
-->1
SELECT
  c.class                                        AS ship_class,
  MIN(b.date)                 		   			 AS first_battle_year,
  MAX(b.date)                					 AS last_battle_year,
  COUNT(DISTINCT b.name)                         AS battles_count
FROM Classes AS c
LEFT JOIN Ships    AS s ON s.class = c.class
LEFT JOIN Outcomes AS o ON o.ship  = s.name
LEFT JOIN Battles  AS b ON b.name  = o.battle
WHERE c.class LIKE 'N%'    -- само класове, започващи на 'N'
GROUP BY c.class
ORDER BY c.class;
-->2 
SELECT
  b.name AS battle_name
FROM Battles   AS b
JOIN Outcomes  AS o ON o.battle = b.name
JOIN Ships     AS s ON s.name   = o.ship
JOIN Classes   AS c ON c.class  = s.class
GROUP BY b.name
HAVING
     SUM(CASE WHEN c.type = 'bb' THEN 1 ELSE 0 END)
   > SUM(CASE WHEN c.type = 'bc' THEN 1 ELSE 0 END)
ORDER BY b.name;

--13.07.2018
-->1 
SELECT 
S.NAME      AS Studio_name,
MIN(M.YEAR) AS First_movie_year,
MAX(M.YEAR) As Last_movie_year,
COUNT(M.TITLE) AS Number_of_movies
FROM STUDIO as S
JOIN MOVIE as M On S.NAME = M.STUDIONAME
WHERE S.NAME Like 'M%' --> Тука е много по интересно без тази клауза
GROUP by S.NAME
-->2
SELECT MS.name, COUNT(SI.MOVIETITLE) As films_acted
FROM MOVIESTAR AS MS
JOIN STARSIN As SI on MS.NAME = SI.STARNAME
WHERE MS.GENDER = 'F'
GROUP by MS.NAME
ORDER by films_acted DESC
LIMIT 1

--09.09.2017
--1. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе име и държава на корабите,
--които никога не са потъвали в битка (може и да не са участвали).
SELECT name, country
FROM ships LEFT JOIN outcomes ON name=ship
JOIN classes ON ships.class=classes.class
WHERE OUTCOMES.RESULT != 'sunk' and OUTCOMES.RESULT is NULL;
--2. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе име, водоизместимост и брой
--оръдия на най-леките кораби с най-много оръдия.
SELECT name, displacement, numguns
FROM classes c JOIN ships s ON s.class=c.class
WHERE displacement = (SELECT MIN(displacement)
FROM classes) AND
numguns = (SELECT MAX(c1.numguns)
FROM classes c1
WHERE c1.DISPLACEMENT = (SELECT MIN(displacement)
FROM classes));
--3. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе име на битките, в които е
--участвал един кораб.
SELECT battle
FROM outcomes o1
WHERE EXISTS (SELECT *
FROM outcomes o2
WHERE o2.BATTLE = o1.BATTLE
GROUP by o2.BATTLE
HAVING count(*) = 1);
--4. Да се посочи заявката, която извежда име на класа и брой на потъналите в битка кораби за съответния клас, за
--тези класове с повече от 5 кораба.
-->Отговор Б

--11.07.2017
--1. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе за всяко студио името на
--студиото, заглавието и годината на филма, излязъл последно на екран за това студио.
SELECT studioname, title, year
FROM movie m
WHERE year = (SELECT MAX(year)
FROM movie
WHERE m.STUDIONAME = studioname);

--2. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе име на продуцент и обща
--дължина на продуцираните от него филми, за тези продуценти, които имат поне един филм преди 1980 г.
SELECT name, SUM(length)
FROM movieexec JOIN movie ON producerc = cert
WHERE name in (SELECT name FROM MOVIEEXEC JOIN movie ON producerc = cert WHERE year < 1980)
GROUP by name;

--3. Попълнете липсващите части, обозначени с ______ така, че заявката да изведе име на актьорите, участвали
--във филми на продуценти с най-големи нетни активи, както и заглавие на филмите, в които са участвали, име на
--продуцент и нетни активи.
SELECT starname, title, name, networth
FROM starsin JOIN movie ON movietitle=title AND movieyear=year
JOIN (SELECT cert, networth, name
FROM movieexec
WHERE networth in (SELECT MAX(networth) FROM MOVIEEXEC)) t
on t.cert = producerc;

--4 отгвор В "= ANY()" еквивалентно на "IN"
SELECT MOVIEEXEC.name, MOVIE.title, MOVIE.year
FROM movie 
JOIN movieexec ON producerc = cert
WHERE cert IN (SELECT producerc
FROM movie
WHERE title='Ice Age');

--09.09.2016
--1 . Да се посочи заявката, която извежда всички държави, които имат поне един кораб, участвал в
-- битка, както и броя на потъналите кораби за всяка от държавите.
--Отговор Б
SELECT c.country , COUNT(o.result)
FROM classes c JOIN ships s ON c.class=s.class
JOIN outcomes o ON s.name=o.ship
WHERE result='sunk'
GROUP BY c.country;
--2
--Да се посочи заявката, която извежда имената на битките, които са по-мащабни (с кораби от повече
--държави) от битката в Коралово море (Coral Sea).
--Отговор А
SELECT DISTINCT battle
FROM outcomes o1
WHERE
(SELECT COUNT(DISTINCT country)
FROM outcomes o,ships s,classes c
WHERE o.ship=s.name AND s.class=c.class AND battle=o1.battle)
>
(SELECT count(DISTINCT country)
FROM outcomes o,ships s,classes c
WHERE o.ship=s.name AND s.class=c.class AND battle='Coral Sea')

--12.07.2016
--1 Да се посочи заявката, която извежда името на продуцента и имената на филмите,
--продуцирани от продуцента на 'Pretty Woman'. Възможно е името на продуцента на филма да
--не е известно.
--Отговор A
SELECT t.name, title
FROM movie m JOIN (SELECT name, cert
FROM movieexec
WHERE cert IN (SELECT producerc
FROM movie
WHERE title='Pretty Woman')) t
ON m.producerc=t.cert;
--2 2. Да се посочи заявката, която за актьорите, участвали в най много филми на съответното
--студио, извежда име на студио, име на актьор и брой филми, в които е участвал актьорът. В
--резултата не трябва да се включват филми, за които името на студиото не е известно.
--Отговор 



