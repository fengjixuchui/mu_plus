/** @file -- DfciPasswordLibNull.c
Contains base logic for querying, setting, and verifying user passwords.

Copyright (c) 2015, Microsoft Corporation. All rights reserved.

**/

#include <DfciSystemSettingTypes.h>
#include <Library/DfciPasswordLib.h>      // Public header for declaring interfaces, prototypes.

/**
  Performs any initialization that is necessary for the functions in this
  library to behave as expected.

  Only necessary to run once per boot.
  Published as a public function so that it can be invoked in a useful driver.

  @retval     EFI_SUCCESS   Initialization is complete.
  @retval     Others        Something went wrong. Investigate further.

**/
EFI_STATUS
InitializePasswordLib (
  VOID
  )
{

  return EFI_SUCCESS;
}

/**
  Deletes all passwords and resets password infrastructure to factory condition.
  Published as a public function so that it can be invoked in a useful driver.

  @retval     EFI_SUCCESS   Reset is complete.
  @retval     Others        Something went wrong. Investigate further.

**/
EFI_STATUS
ResetPasswordLib (
  VOID
  )
{

  return EFI_SUCCESS;
}

/**
  Public interface for validating password strings.

  Will evaluate all current password strength/validity requirements and
  return a BOOLEAN for whether the password is valid. Also uses an optional
  pointer to return a bitmap of which tests failed.

  NOTE: Returns FALSE on NULL strings.

  @param[in]  String    CHAR16 pointer to the string that's being evaluated.
  @param[out] Failures  [Optional] Pointer to a UINT32 that will have bits (defined
                        in DfciPasswordLib.h) set according to which tests may have failed.
                        If NULL, will not return a test bitmap and will fail ASAP.

  @retval     TRUE      Password is valid. "Failures" should be 0.
  @retval     FALSE     Password is invalid. "Failures" will have bits set for which tests failed.

**/
BOOLEAN
EFIAPI
IsPwStringValid (
  IN  CHAR16          *String,
  OUT PW_TEST_BITMAP  *Failures OPTIONAL
  )
{

  return TRUE;
}

/**
  Public interface for determining whether a given password is set.

  NOTE: Will initialize the Password Store for the given handle if it doesn't exist

  @param[in]  Handle  PW_HANDLE for the password being queried.

  @retval     TRUE    Password is set.
  @retval     FALSE   Password is not set, or an error occurred preventing
                      the check from completing successfully.

**/
BOOLEAN
EFIAPI
IsPasswordSet (
  IN  PW_HANDLE    Handle
  )
{

  return FALSE;
}


/**
  Public interface for setting a new password.

  Will run internal checks on the password before setting it. Returns an
  error if the password cannot be set.

  If CurPassword is NULL and a password is currently set, will pass only if Authentication
  has previously been cached.
  If NewPassword is NULL and a password is currently set, will clear password.

  @param[in]  AuthToken     AuthToken generated by the AuthManager
  @param[in]  NewPassword   [Optional] Pointer to a buffer containing the new password.
                            If NULL, will delete the current password, if set.

  @retval     EFI_SUCCESS             Requested operation has been successfully performed.
  @retval     EFI_SECURITY_VIOLATION  There is something wrong with the formatting or
                                      authentication of the CurPassword.
  @retval     EFI_INVALID_PARAMETER   There is something wrong with the formatting of
                                      the NewPassword.
  @retval     EFI_ABORTED             Something else went wrong with the internal logic.

**/
EFI_STATUS
EFIAPI
SetPassword (
  IN  UINTN          AuthToken,
  IN  CHAR16         *NewPassword
  )
{

  return EFI_UNSUPPORTED;
}

/**
  Public interface for validating a password against the current password.

  If no password is currently set, will return FALSE.

  NOTE: This function does NOT perform string validation on the password
        being authenticated. This is to accomodate changing valid charsets.
        Will still make sure that string does not exceed max buffer size.

  @param[in]  Handle    PW_HANDLE for the password being verified.
  @param[in]  Password  String being evaluated.

  @retval     TRUE      Password matches the stored password for Handle.
  @retval     TRUE      No password is currently set.
  @retval     TRUE      Password is NULL and Handle has previously authenticated successfully.
  @retval     FALSE     No Password is set for Handle.
  @retval     FALSE     Supplied Password does not match stored password for Handle.

**/
BOOLEAN
EFIAPI
AuthenticatePassword (
  IN  PW_HANDLE   Handle,
  IN  CONST CHAR16      *Password
  )
{

  return TRUE;
}

EFI_STATUS
SetPasswordVariable (
  UINT8 *Buffer
  )
{

  return EFI_UNSUPPORTED;
}
