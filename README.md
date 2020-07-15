"%[^:]" => đọc đến dấu 2 chấm thì dừng 

"%*[:]" => xóa hết dấu : ở đầu buffer của scanf, k lưu vào gì cả

" %[^>\n]s" => bỏ qua các khoảng trắng hoặc \n (nếu có) ở đầu buffer, rồi đọc cho đến \n hoặc > lưu vào chuỗi đọc được vào s

"%*[>]" => như "%*[:]"

"%[\n]" => Gần giống " %[^\n]s".
Khác ở chỗ là nếu có \n ở đầu thì nó vẫn đọc. 