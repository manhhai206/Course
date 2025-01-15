#ifndef STD_TYPES_H
#define STD_TYPES_H

#include <stdint.h>

/* ============================================
 * Version Information
 * ============================================ */
/************************************************************
 * @brief Thông tin phiên bản của file Std_Types.h
 * @details Các định nghĩa về việc phiên bản giúp dễ dàng
 *          kiểm soát các thay đổi và tương thích phần mềm
 * **********************************************************/
#define STD_TYPES_SW_MAJOR_VERSION    (1U)  /**<Major version number */
#define STD_TYPES_SW_MINOR_VERSION    (0U)  /**<Minor version number */
#define STD_TYPES_SW_PATCH_VERSION    (0U)  /**<Patch version number */

/* ============================================
 * Standard Return Type
 * ============================================ */
/************************************************************
 * @details Được sử dụng cho các hàm API, với các giá trị 
 *          mặc định là E_OK và E_NOT_OK
 * **********************************************************/

#define E_OK        0x01U   /**<Thao tác thành công */
#define E_NOT_OK    0x00U   /**<Thao tác thất bại */

/* ============================================
 * Logical State Definitions
 * ============================================ */
/************************************************************
 * @brief Định nghĩa các trạng thái logic cao và thấp
 * @details Được sử dụng cho các tín hiệu đầu vào/đầu ra
 * **********************************************************/
#define STD_HIGH    1   /**<Trạng thái logic cao */
#define STD_LOW     0   /**<Trạng thái logic thấp */

/* ============================================
 * Null Pointer Definitions
 * ============================================ */
/************************************************************
 * @brief Định nghĩa con trỏ NULL   
 * @details Con trỏ NULL là con trỏ trỏ đến địa chỉ 0
 * **********************************************************/
#ifndef NULL
    #define NULL  ((void*)0)  /**<Định nghĩa con trỏ NULL */  
#endif

/* ============================================
 * Platform Independent Data Types
 * ============================================ */
/************************************************************
 * @brief Các kiểu dữ liệu độc lập với nền tảng
 * @details Định nghĩa rõ ràng về kích thước và dấu của các kiểu dữ liệu
 * **********************************************************/
typedef unsigned char       uint8;   /**<Số nguyên không dấu 8 bit */
typedef signed char         sint8;   /**<Số nguyên có dấu 8 bit */
typedef unsigned short      uint16;  /**<Số nguyên không dấu 16 bit */
typedef signed short        sint16;  /**<Số nguyên có dấu 16 bit */
typedef unsigned long       uint32;  /**<Số nguyên không dấu 32 bit */
typedef signed long         sint32;  /**<Số nguyên có dấu 32 bit */
typedef unsigned long long  uint64;  /**<Số nguyên không dấu 64 bit */
typedef signed long long    sint64;  /**<Số nguyên có dấu 64 bit */

typedef float       float32;    /**<Số thực 32 bit */
typedef double      float64;    /**<Số thực 64 bit */
		
/* ============================================
 * Standard Return Type
 * ============================================ */
/************************************************************
 * @typedef Std_ReturnType
 * @brief Kiểu trả về tiêu chuẩn
 * **********************************************************/
typedef uint8 Std_ReturnType;

/* ============================================
 * Boolean Types Definitions
 * ============================================ */
/************************************************************
 * @typedef boolean
 * @brief Kiểu dữ liệu boolean
 * @details Được sử dụng để biễu diễn giá trị đúng sai
 * **********************************************************/
typedef uint8 boolean;

#ifndef TRUE
    #define TRUE        1U /**<Giá trị Boolean TRUE */
#endif

#ifndef FALSE
    #define FALSE       0U /**<Giá trị Boolean FALSE */
#endif

/* ============================================
 * version Information Structure
 * ============================================ */
/************************************************************
 * @typedef Std_VersionInforType
 * @brief Cấu trúc thông tin phiên bản
 * @details Cấu trúc này lưu thông tin phiên bản mềm 
 *          của một module
 * **********************************************************/
typedef struct 
{
    uint16 vendorID;            /**<ID nhà cung cấp */
    uint16 moduleID;            /**<ID module */
    uint8  sw_major_version;     /**<Phiên bản chính của phần mềm */
    uint8  sw_minor_version;     /**<Phiên bản phụ của phần mềm */
    uint8  sw_patch_version;     /**<Phiên bản sửa lỗi của phần mềm */
} Std_VersionInfoType;

/* ============================================
 * Development Error Tracer (DET) Report Error Macro
 * ============================================ */
/************************************************************
 * @brief Macro báo lỗi cho Development Error Tracer (DET)
 * @details Được sử dụng để ghi nhận lỗi phát triển trong quá trình chạy.
 * **********************************************************/
#define Det_ReportError(ModuleID, InstanceID, ApiID, ErrorID)       /**<Báo cáo lỗi cho DET */

/* ============================================
 * Active/Idle State Definitions
 * ============================================ */
/************************************************************
 * @brief Định nghĩa trạng thái hoạt động/nhàn rỗi.
 * @details Được sử dụng trong các trạng thái hệ thống.
 * **********************************************************/
#define STD_ACTIVE  0x01U    /**<Trạng thái active */
#define STD_IDLE    0x00U    /**<Trạng thái idle */

/* ============================================
 * On/Off State Definitions
 * ============================================ */
/************************************************************
 * @brief Định nghĩa trạng thái bật/tắt.
 * @details Được sử dụng để điều khiển trạng thái bật/tắt.
 * **********************************************************/
#define STD_ON     0x01U    /**<Trạng thái ON */
#define STD_OFF    0x00U    /**<Trạng thái OFF */

#endif /*STD_TYPES_H */
