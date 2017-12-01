<head>
<meta http-equiv="Content-type" content="text/html;charset=utf-8"/>
</head>
<?

		include ("dblib.php");
		$response = array();

		$email = $_POST['email'];
		$password = $_POST['password'];
		$account= $_POST['account'];

		$connect = mysqli_connect($host,$user,$pass,$user) or die("SQL server에 연결할 수 없습니다."); 
		//mysql_select_db($db,$connect);
		
		
		$result=mysqli_query($connect,"select email from user");
		$equal=1;
		while($response=mysqli_fetch_array($result))
		{
			if(strcmp($response['email'],$email)==0)
				$equal=0;
		}
		if($equal==1)
		{
			if(strpos($email,"@")>=0 && strpos($email,".")>=0)  // email 형식 
			{
					$qry="insert into user values(NULL,'$email','$password','$account',0,0)";
					$result = mysqli_query($connect,$qry);
			
					echo "1:Success!<br>";
					echo "E-Mail:".$email."<br>"."Password:"."[암호화]"."<br>"."Account:".$account;
			}
			else{
					echo "3:No Email Form!! Not @";
			}
		
		
			
		}
		else
		{
			echo "0:Equal Email!<br>";
			echo "E-Mail:".$email."<br>"."Password:"."[암호화]"."<br>"."Account:".$account;
		}
		
	
  

	echo "<br><a href='admin.php'>관리자페이지로</a>";


	mysqli_close($connect);
?>