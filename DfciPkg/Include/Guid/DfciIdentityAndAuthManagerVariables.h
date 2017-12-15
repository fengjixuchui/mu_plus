/* @file
Contains definitions for Identity and Authentication Manager variables.  

This variable is used to provision or change the Authentication Manager Certificates

Copyright (c) 2015, Microsoft Corporation. All rights reserved.

**/

#ifndef __DFCI_IDENTITY_AND_AUTH_MANAGER_VARIABLES_H__
#define __DFCI_IDENTITY_AND_AUTH_MANAGER_VARIABLES_H__

//
// Variable namespace
//
extern EFI_GUID gDfciAuthProvisionVarNamespace;

#define DFCI_IDENTITY_AUTH_PROVISION_SIGNER_VAR_NAME          L"SignerProvision"
#define DFCI_IDENTITY_AUTH_PROVISION_SIGNER_RESULT_VAR_NAME   L"SignerProvisionResult"
#define DFCI_IDENTITY_AUTH_PROVISION_SIGNER_VAR_ATTRIBUTES    (EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS) 


#define DFCI_IDENTITY_AUTH_PROVISION_APPLY_VAR_SIGNATURE     SIGNATURE_32('M','S','P','A')
#define DFCI_IDENTITY_AUTH_PROVISION_RESULT_VAR_SIGNATURE    SIGNATURE_32('M','S','P','R')

#define DFCI_IDENTITY_AUTH_PROVISION_VAR_VERSION (1)


#define MAX_ALLOWABLE_DFCI_IDENTITY_AUTH_PROVISION_APPLY_VAR_SIZE (1024 * 16)  

#define DFCI_SIGNER_PROVISION_IDENTITY_INVALID (0)
#define DFCI_SIGNER_PROVISION_IDENTITY_OWNER (1)
#define DFCI_SIGNER_PROVISION_IDENTITY_USER (2)
#define DFCI_SIGNER_PROVISION_IDENTITY_USER1 (3)
#define DFCI_SIGNER_PROVISION_IDENTITY_USER2 (4)

#pragma warning(push)
#pragma warning(disable: 4200) // zero-sized array
#pragma pack (push, 1)

typedef struct {
  UINT32 HeaderSignature;   // 'M', 'S', 'P', 'A'
  UINT8  HeaderVersion;     // 1
  UINT8  Identity;          // Owner = 1, User = 2, User1 = 3, User2 = 4
  UINT64 SerialNumber;      // Target a single device.  If 0 then it works on any device.  If non zero then it will only apply to a device with that serial number
  UINT32 SessionId;         // Unique id for this attempt.  This is zero when hashed
  UINT16 TrustedCertSize;   // Size of the Trusted Cert Data  //for delete requests this can be size 0
  UINT8  TrustedCert[];     // Trusted Cert data that will be provisioned  (der ecoded cert file)
  //WIN_CERT TestSignature; // The Test Signature  (not required when TrustedCertSize is 0).  
                            // The Test signature is of the TrustedCert using the a key that verifies against the trusted cert.
                            // This is used to make sure the TrustedCert that will be provisioned is capabile of verifying signatures.  
   
  //WIN_CERT Signature;     //Signature Auth data - Signature covers all data in this struct except SessionId is 0.  
} DFCI_SIGNER_PROVISION_APPLY_VAR;

typedef struct {
  UINT32 HeaderSignature;   // 'M', 'S', 'P', 'R'
  UINT8  HeaderVersion;     // 1
  UINT8  Identity;          // Owner = 1, User = 2, User1 = 3, User2 = 4
  UINT32 SessionId;         // Session Id of the apply var that this result is for
  UINT64 StatusCode;        // Status code showing result or error.  0 = Success.  Non-zero = Error
} DFCI_SIGNER_PROVISION_RESULT_VAR;

#pragma pack (pop)
#pragma warning(pop)


#endif // __DFCI_IDENTITY_AND_AUTH_MANAGER_VARIABLES_H__
