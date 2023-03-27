-- 관계형 데이터 베이스

-- SQL
-- Database에 질문을 날린다.

-- 기본키 : 중복을 허용하지 않고, NULL값이 올 수 없다.

-- dbo 라는 데이터 베이스에서 players 테이블에 모든 걸 출력 해주세요.

-- FROM.. 어떤 Table에서
-- WHERE ..어떠한 조건으로
-- SELECT..속성을 선택하겠다.
-- ORDER BY...정렬 ASC(오름차순), DESC(내림차순)

-- players 테이블에서 birthYear가 1934인 사람의 모든 정보 추출
USE BaseballData

SELECT *
FROM players
WHERE (birthYear > 1934 OR birthCountry = 'USA') AND deathYear IS NOT NULL

SELECT nameFirst as 성,nameLast as 이름
FROM dbo.players

-- players 테이블에서 birthCountry가 USA이면서 1869년에 태어난 사람의 lahmanID, playerID, 성과 이름을 추출해주세요
-- 이정보를 birthMonth 순으로 보여주세요, 단 birthMonth가 NULL이 아닌 얘들만
SELECT TOP(1) *
FROM players
WHERE birthCountry = 'USA' AND birthYear = 1869 AND birthMonth IS NOT NULL
ORDER BY players.birthMonth ASC
-- LIMIT 1

-- players 테이블에서 birthCity가 NULL 아닌 얘들을 중복을 허락하지 않고 뽑아주세요,
-- birthCity 사전순으로 정렬까지해서 보여주세요.
SELECT DISTINCT birthCity 
FROM players
WHERE birthCity IS NOT NULL
ORDER BY birthCity

-- SQL MSDN
-- https://learn.microsoft.com/ko-kr/sql/t-sql/language-elements/like-transact-sql?view=sql-server-ver16

-- 패턴으로 문자열 출력하기
-- players 테이블에서 birthCity가 "New"로 시작하는 birthCity를 보여주세요.
-- '문자열%' ... 문자열 + 아무거나
SELECT DISTINCT birthCity
FROM players
WHERE birthCity LIKE 'New%'

-- New_ _ _ _ _
-- players 테이블에서 birthCity가 "New"로 시작하는 birthCity를 보여주세요.
SELECT DISTINCT birthCity
FROM players
WHERE birthCity LIKE 'New_____'

-- varchar ...13/04/1954 => DATETIME 변환이 된다.
SELECT lahmanID, CONVERT(DATETIME,debut) as debutTime
FROM players
WHERE players.debut IS NOT NULL
ORDER BY debutTime

-- 집계함수

-- players에서 birthYear가 1950에 해당하는 사람 명수
SELECT COUNT(lahmanID)
FROM players
WHERE birthYear = 1950

-- players에서 birthYear의 평균
SELECT AVG(birthYear) as 평균생년
FROM players
WHERE birthYear IS NOT NULL

-- players에서 살아계신 분들의 나이(100세 이상은 제외)의 평균을 뽑아주세요.
SELECT AVG(2023 - birthYear) as 평균나이
FROM players
WHERE birthYear IS NOT NULL AND (2023 - birthYear) < 100 AND deathYear IS NULL

-- players에서 살아계신 분들의 나이(100세 이상은 제외) 중에 최소령자의 이름과 나이를 뽑아주세요
SELECT nameFirst, nameLast, (2023 - birthYear)
FROM players
WHERE (2023 - birthYear) = 
(SELECT MIN(2023 - birthYear) as 최소령나이
FROM players
WHERE birthYear IS NOT NULL AND (2023 - birthYear) < 100 AND deathYear IS NULL) -- SubQuery

-- player에서 평균 몸무게 출력, NULL
SELECT AVG(
CASE
WHEN weight IS NULL THEN 0
ELSE weight END
)
FROM players

SELECT *
FROM batting

SELECT *
FROM players

-- 보스턴 소속 선수들은 총 몇명입니까
SELECT DISTINCT COUNT(*) as 명
FROM batting
WHERE teamID = 'BOS'

-- 기본키 : 테이블에서 NULL이 허용이되지 않고, 중복이 허용되지 않는 고유키(레드블랙트리 알고리즘)
-- 외래키 : 두 테이블간 매칭이 될 수 있는 키

-- BOS소속에서 홈런을 제일 많이친 선수의 이름을 출력주세요.
SELECT nameFirst, nameLast
FROM players
WHERE players.playerID = 
(
SELECT TOP (1) playerID
FROM batting
WHERE teamID = 'BOS'
ORDER BY HR DESC
)

-- FROM			책상에서
-- WHERE		공을
-- GROUP BY		색대로 분류해서
-- HAVING		분류한 공들 중에 빨강공은 빼고
-- SELECT		갖고와주세요
-- ORDER BY		크기별로 나열해주세요

-- GROUP BY... 집계함수랑 많이 쓰인다. AVG, SUM, COUNT

SELECT *
FROM batting

-- 각 팀들이 2000년도에 친 홈런의 개수를 합해서 보여주세요.
SELECT teamID , yearID ,SUM(HR) as SUM_HR
FROM batting
WHERE yearID = 2000
GROUP BY teamID, yearID
ORDER BY SUM_HR DESC

-- 각 팀들이 2000년도에 친 홈런의 개수를 합해서 보여주세요.(이 때 개수가 200이상인 얘들만 보여주세요)
SELECT teamID , yearID ,SUM(HR) as SUM_HR
FROM batting
WHERE yearID = 2000
GROUP BY teamID, yearID
HAVING SUM(HR) >= 200

UNION ALL-- 컬럼이 일치해야된다. UNION, UNION ALL 차이는 중복제거

SELECT teamID , yearID ,SUM(HR) as SUM_HR
FROM batting
WHERE yearID = 1999
GROUP BY teamID, yearID
HAVING SUM(HR) >= 200

-- 두 테이블을 합치는 방법
-- Cross Join
-- Inner Join
SELECT *
FROM batting

SELECT *
FROM salaries

-- INNER JOIN : salaries에서 players 테이블과 겹치는 것을 salaries 기준으로 출력
SELECT *
FROM players
	INNER JOIN salaries
	ON salaries.playerID = players.playerID

-- Outer Join
SELECT *
FROM salaries
	LEFT JOIN players
	ON salaries.playerID = players.playerID

	SELECT *
	FROM salaries

	SELECT *
	FROM batting

	-- salaries와 batting 참고해서 각 년도에 teamID, 친 홈런 갯수, 벌어들인 연봉의 합 
	SELECT salaries.yearID, salaries.teamID, SUM(batting.HR) as SUMHR, SUM(salaries.salary) as SUMSALARY
	FROM salaries
		LEFT JOIN batting
		ON salaries.playerID = batting.playerID AND salaries.yearID = batting.yearID AND salaries.teamID = batting.teamID
	GROUP BY salaries.yearID, salaries.teamID