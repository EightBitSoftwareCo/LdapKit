/*
 *  LDAP Kit
 *  Copyright (c) 2012, Bindle Binaries
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_START@
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Bindle Binaries nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL BINDLE BINARIES BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
 *
 *  @BINDLE_BINARIES_BSD_LICENSE_END@
 */
/**
 *  LdapKit/LKResult.h returns results from LDAP operations.
 */

#import <Foundation/Foundation.h>
#import <LdapKit/LKEnumerations.h>


#pragma mark LDAP result type
enum ldap_kit_ldap_result_type
{
   LKLdapResultTypeConnect           = 0x01,
   LKLdapResultTypeUnbind            = 0x02,
   LKLdapResultTypeSearch            = 0x03,
   LKLdapResultTypeUnknown           = 0x00
};
typedef enum ldap_kit_ldap_result_type LKLdapResultType;


@class LKError;
@class LKSession;


@interface LKResult : NSOperation
{
   // state information
   LKSession              * session;
   LKError                * error;
   LKLdapResultType         resultType;

   // server information
   NSString               * ldapURI;
   LKLdapProtocolScheme     ldapScheme;
   LKLdapProtocolVersion    ldapProtocolVersion;

   // encryption information
   LKLdapEncryptionScheme   ldapEncryptionScheme;
   NSString               * ldapCACertificateFile;

   // timeout information
   NSInteger                ldapSearchTimeout;
   NSInteger                ldapNetworkTimeout;

   // authentication information
   LKLdapBindMethod         ldapBindMethod;
   NSString               * ldapBindWho;
   NSData                 * ldapBindCredentials;
   NSString               * ldapBindSaslMechanism;
   NSString               * ldapBindSaslRealm;

   // client information
   NSInteger                tag;
   id                       object;
}

/// @name state information
@property (nonatomic, readonly) LKError                * error;
@property (nonatomic, readonly) LKLdapResultType         resultType;

/// @name client information
@property (nonatomic, assign)   NSInteger                tag;
@property (nonatomic, retain)   id                       object;

/// @name Object Management Methods
- (id) initLdapInitialzieWithSession:(LKSession *)session;

/// @name LDAP tasks
- (BOOL) connect;
//- (BOOL) search;
- (BOOL) testConnection;
- (BOOL) unbind;

/// @name LDAP subtasks
- (LDAP *) connectBind:(LDAP *)ld;
- (LDAP *) connectFinish:(LDAP *)ld;
- (LDAP *) connectInitialize;
- (LDAP *) connectStartTLS:(LDAP *)ld;

@end