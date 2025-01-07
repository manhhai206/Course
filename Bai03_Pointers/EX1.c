#include <stdio.h>
#include <string.h>

typedef struct {
   char ten[50];
   float diemTrungBinh;
   int id;
} SinhVien;

/***********************************************************************
 * @brief So sánh hai chuỗi ký tự
 * Hàm so sánh chuỗi ký tự `str1` và `str2` theo thứ tự từ điển.
 * Duyệt từng ký tự của hai chuỗi cho đến khi:
 * - Gặp ký tự khác nhau, hoặc
 * - Gặp ký tự kết thúc chuỗi (`'\0'`).
 * @param[in] str1 Chuỗi ký tự thứ nhất
 * @param[in] str2 Chuỗi ký tự thứ hai
 * @return int 
 * - 0 nếu hai chuỗi bằng nhau.
 * - Giá trị âm nếu chuỗi `str1` nhỏ hơn `str2`.
 * - Giá trị dương nếu chuỗi `str1` lớn hơn `str2`.
 ************************************************************************* */
int stringCompare(const char *str1, const char *str2) 
{
   while (*str1 && (*str1 == *str2)) 
   {
       str1++;
       str2++;
   }
   return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

/***********************************************************************
 * @brief Hàm so sánh hai sinh viên theo tên
 * @param[in] a Con trỏ đến sinh viên thứ nhất (SinhVien).
 * @param[in] b Con trỏ đến sinh viên thứ hai (SinhVien).
 * @return int 
 * - 0 nếu hai tên sinh viên bằng nhau.
 * - Giá trị âm nếu tên của sinh viên `a` nhỏ hơn tên của sinh viên `b`.
 * - Giá trị dương nếu tên của sinh viên `a` lớn hơn tên của sinh viên `b`.
 ************************************************************************/
int compareByName(const void *a, const void *b) 
{
    // Ép kiểu từ void* sang SinhVien*
    SinhVien *sv1 = (SinhVien *)a;
    SinhVien *sv2 = (SinhVien *)b;

    // So sánh tên của hai sinh viên bằng hàm stringCompare
    return stringCompare(sv1->ten, sv2->ten);
}

/***********************************************************************
 * @brief Hàm so sánh điểm trung bình
 * @param[in] a Con trỏ đến điểm thứ nhất (SinhVien).
 * @param[in] b Con trỏ đến điểm thứ hai (SinhVien).
 * @return int 
 * - Giá trị 0 nếu điểm `a` nhỏ hơn diểm `b`.
 * - Giá trị dương nếu điểm `a` lớn hơn diểm `b`.
 ************************************************************************/
int compareByDiemTrungBinh(const void *a, const void *b) 
{
    // Ép kiểu từ void* sang SinhVien*
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;

    // So sánh điểm trung bình
   if (sv1->diemTrungBinh > sv2->diemTrungBinh)
   {
        return 1;
   } 
   return 0;
}

/***********************************************************************
 * @brief Hàm so sánh ID
 * @param[in] a Con trỏ đến ID thứ nhất (SinhVien).
 * @param[in] b Con trỏ đến ID thứ hai (SinhVien).
 * @return int 
 * - Giá trị 0 nếu điểm `a` nhỏ hơn diểm `b`.
 * - Giá trị dương nếu điểm `a` lớn hơn diểm `b`.
 ************************************************************************/
int compareByID(const void *a, const void *b) 
{
   // Ép kiểu từ void* sang SinhVien*
   SinhVien *sv1 = (SinhVien *)a;
   SinhVien *sv2 = (SinhVien *)b;
   return sv1->id - sv2->id;
}


/***********************************************************************
 * @brief Hàm sắp xếp chung
 * @param[in] array Mảng chứa thông tin (SinhVien).
 * @param[in] size Kích thước của mảng truyền vào.in
 * @param[in] int (*compareFunc)(const void *, const void *)
 *            con trỏ hàm dùng để trỏ đến hàm tại thời điểm
 *            runtime.
 ************************************************************************/
void sort(SinhVien array[], size_t size, int (*compareFunc)(const void *, const void *)) {
   int i, j;
   SinhVien temp;
   for (i = 0; i < size-1; i++)    
       for (j = i+1; j < size; j++)
           if (compareFunc(array+i, array+j)>0) {
               temp = array[i];
               array[i] = array[j];
               array[j] = temp;
           }
}


/***********************************************************************
 * @brief Hàm hiển thị thông tin của sinh viên.
 * @param[in] array Mảng chứa thông tin (SinhVien).
 * @param[in] size Kích thước của mảng truyền vào.
 ************************************************************************/
void display(SinhVien *array, size_t size) 
{
    for (size_t i = 0; i < size; i++) 
    {
        printf("ID: %d, Ten: %s, Diem Trung Binh: %.2f\n", array[i].id, array[i].ten, array[i].diemTrungBinh);
    }
   printf("\n");
}


int main() 
{
    SinhVien danhSachSV[] = {
       {  
           .ten = "Hoang",
           .diemTrungBinh = 7.5,
           .id = 100
       },

       {
           .ten = "Tuan",
           .diemTrungBinh = 4.5,
           .id = 101
       },
       
       {
           .ten = "Vy",
           .diemTrungBinh = 6.8,
           .id = 102},
       {  
           .ten = "Ngan",
           .diemTrungBinh = 5.6,
           .id = 10
       },
    };

  size_t size = sizeof(danhSachSV) / sizeof(danhSachSV[0]);

   // Sắp xếp theo tên
   sort(danhSachSV, size, compareByName);
   printf("Theo Ten\n");
   display(danhSachSV, size);

   // Sắp xếp theo điểm trung bình
   sort(danhSachSV, size, compareByDiemTrungBinh);
   printf("Theo Diem Trung Binh\n");
   display(danhSachSV, size);

   // Sắp xếp theo ID
   sort(danhSachSV, size, compareByID);
   printf("Theo ID\n");
   display(danhSachSV, size);

   return 0;
}