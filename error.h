#ifndef ERROR_H
#define ERROR_H

/**
 * @brief       Error codes for use across the program.
 */
enum EError {
        SUCCESS                 = 0,    /**< No error occured, or success.    */
        FILE_NOT_FOUND          = -1,   /**< File could not be opened.        */
        NULL_ARG                = -2,   /**< An argument was NULL.            */
        FILE_OPERATION_ERR      = -3,   /**< File operation failed, eg. fseek.*/
        BUFFER_TOO_SMALL        = -4,   /**< The given buffer was too small.  */ 
        ARG_NOT_NULL            = -5,   /**< An arg  was not NULL as expeced. */
        FILE_ZERO_LENGTH        = -6,   /**< The file was of zero length.     */
        OUT_OF_MEMORY           = -7,   /**< For example malloc failed        */
        ELF_FORMAT_INVALID      = -8,   /**< ELF is not valid format.         */
        INVALID_MACHO           = -9,   /**< MACH-O was invalid.              */
        MACH_NOT_SUPPORTED      = -10   /**< MACH-O type not supported yet.   */
};

#endif /* ERROR_H */
